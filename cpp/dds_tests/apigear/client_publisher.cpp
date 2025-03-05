#include "client_publisher.h"
#include <fastrtps/Domain.h>
#include "apigear/utilities/threadpool.h"
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/core/LoanableSequence.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>


namespace {
    void fill_topics_matched(std::map<std::string, bool>& map_to_fill)
    {
        map_to_fill["prop_propInt"] = false;
    }
}


ClientPublisher::ClientPublisher(eprosima::fastdds::dds::DomainParticipant* participant)
    :m_participant(participant)
{
    mp_publisher = m_participant->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT);
    if (mp_publisher == nullptr)
    {
        std::cerr << "Failed to create Publisher!" << std::endl;
    }
}

void ClientPublisher::init()
{
    fill_topics_matched(topics_matched);
    m_propertyChangedWriter = createTopicPublisher("prop_propInt", "HelloWorld");
    //mp_methodWriter = createTopicPublisher("rpc.funcInt", "HelloWorld");
    m_requests_pool = std::make_unique<ApiGear::Utilities::ThreadPool>(1);
};

ClientPublisher::~ClientPublisher() {
    if (mp_methodWriter != nullptr)
    {
        mp_publisher->delete_datawriter(mp_methodWriter);
    }
    if (m_propertyChangedWriter != nullptr)
    {
        mp_publisher->delete_datawriter(m_propertyChangedWriter);
    }
    if (mp_publisher != nullptr)
    {
        m_participant->delete_publisher(mp_publisher);
    }
    for (auto topic : topics)
    {
        m_participant->delete_topic(topic);
    }
};

eprosima::fastdds::dds::DataWriter* ClientPublisher::createTopicPublisher(std::string topic, std::string dataType)
{
    eprosima::fastdds::dds::Topic* topic_obj = m_participant->create_topic(topic, dataType, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
    if (!topic_obj)
    {
        std::cerr << "Failed to create Topic: " << topic << std::endl;
        return nullptr;
    }
    topics.push_back(topic_obj);

    return mp_publisher->create_datawriter(topic_obj, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT, this);
}

void ClientPublisher::on_publication_matched(eprosima::fastdds::dds::DataWriter* writer, const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{
    auto element = topics_matched.find(writer->get_topic()->get_name());
    if (element == topics_matched.end())
    {
        //TODO log unexpected topic
        return;
    }
    element->second = info.current_count != 0;

    if (info.current_count_change > 0)
    {
        std::cout << "Publisher matched. " << writer->get_topic()->get_name() << std::endl;
    }
    else if (info.current_count_change < 0)
    {
        std::cout << "Publisher unmatched. " << writer->get_topic()->get_name() << std::endl;
    }
}

bool ClientPublisher::_is_ready()
{
    bool all_matched = std::find_if(topics_matched.begin(), topics_matched.end(), [](auto& element) {return element.second == false; })
        == topics_matched.end();
    return topics_matched.size() > 0 && all_matched;
}

void ClientPublisher::run(uint32_t samples, uint32_t sleep)
{
    for (uint32_t i = 0; i < samples; ++i)
    {
        if (!publish(i))
        {
            --i;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }

}

bool ClientPublisher::publish(int value)
{
    if (_is_ready())
    {
        HelloWorld hello_;
        hello_.message("pubProp");
        hello_.index(value);
        m_propertyChangedWriter->write(&hello_);
        std::cout << "Message: " << hello_.message() << " with index: " << hello_.index()
            << " SENT" << std::endl;
        return true;
    }
    return false;
}