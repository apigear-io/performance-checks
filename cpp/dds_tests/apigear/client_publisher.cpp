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
    m_propertyChangedWriter = createTopicPublisher("prop.propInt", "HelloWorld");
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
    eprosima::fastdds::dds::Topic* topic_obj = m_participant->create_topic("prop_propInt", "HelloWorld", eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
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
    if (n_matched < info.total_count)
    {
        std::cout << "Publisher matched." << std::endl;
        firstConnected = true;
    }
    else if (n_matched > info.total_count)
    {
        std::cout << "Publisher unmatched." << std::endl;
    }
    n_matched = info.total_count;
    //TODO check if matched for all topics!
}

bool ClientPublisher::isReady()
{
    std::cout << "ready ? " << firstConnected && n_matched;
    return firstConnected && n_matched > 0;
}

void ClientPublisher::run(uint32_t samples, uint32_t sleep)
{
    for (uint32_t i = 0; i < samples; ++i)
    {
        if (!publish(i))
        {
            --i;
        }
        else
        {
            std::cout << "Message: " << hello_.message() << " with index: " << hello_.index()
                << " SENT" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }

}

bool ClientPublisher::publish(int value)
{
    if (isReady())
    {
        hello_.index(value);
        m_propertyChangedWriter->write(&hello_);
        return true;
    }
    return false;
}