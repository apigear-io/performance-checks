#include "service_publisher.h"
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
        map_to_fill["set_propInt"] = false;
        map_to_fill["sig_sigInt"] = false;
    }
}


ServicePublisher::ServicePublisher(eprosima::fastdds::dds::DomainParticipant* participant)
    :m_participant(participant)
{
    mp_publisher = m_participant->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT);
    if (mp_publisher == nullptr)
    {
        std::cerr << "Failed to create Publisher!" << std::endl;
    }
}

void ServicePublisher::init()
{
    fill_topics_matched(topics_matched);
    m_propertyChangedWriter = createTopicPublisher("set_propInt", "HelloWorld");
    mp_singalEmitWriter = createTopicPublisher("sig_sigInt", "HelloWorld");
    m_requests_pool = std::make_unique<ApiGear::Utilities::ThreadPool>(1);
};

ServicePublisher::~ServicePublisher() {
    if (mp_singalEmitWriter != nullptr)
    {
        mp_publisher->delete_datawriter(mp_singalEmitWriter);
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

eprosima::fastdds::dds::DataWriter* ServicePublisher::createTopicPublisher(std::string topic, std::string dataType)
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

void ServicePublisher::on_publication_matched(eprosima::fastdds::dds::DataWriter* writer, const eprosima::fastdds::dds::PublicationMatchedStatus& info)
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
        std::cout << "Publisher matched." << std::endl;
    }
    else if (info.current_count_change < 0)
    {
        std::cout << "Publisher unmatched." << std::endl;
    }
 }

bool ServicePublisher::_is_ready()
{
    bool all_matched = std::find_if(topics_matched.begin(), topics_matched.end(), [](auto& element) {return element.second == false; })
        == topics_matched.end();
    return topics_matched.size() > 0 && all_matched;
}


bool ServicePublisher::publishProp(int value)
{
    if (_is_ready())
    {
        HelloWorld hello_;
        hello_.message("pub set prop");
        hello_.index(value);
        m_propertyChangedWriter->write(&hello_);
        return true;
    }
    return false;
}

bool ServicePublisher::publishSig(int value)
{
    if (_is_ready())
    {
        HelloWorld hello_;
        hello_.message("pub Signal");
        hello_.index(value);
        mp_singalEmitWriter->write(&hello_);
        return true;
    }
    return false;
}