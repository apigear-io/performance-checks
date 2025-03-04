#include "service_subscriber.h"
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



ServiceSubscriber::ServiceSubscriber(eprosima::fastdds::dds::DomainParticipant* paritcipant, std::shared_ptr< Cpp::Api::ITestApi0> api)
    : m_paritcipant(paritcipant),
    m_api(api),
    n_matched(0)
{
    m_subscriber = m_paritcipant->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);
}
void ServiceSubscriber::init() 
{
    m_topicReaders.push_back(createTopicSubscriber("prop_propInt", "HelloWorld"));
}
eprosima::fastdds::dds::DataReader* ServiceSubscriber::createTopicSubscriber(std::string topic, std::string dataType)
{
    eprosima::fastdds::dds::Topic* a_topic = m_paritcipant->create_topic(topic, dataType, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
    topics.push_back(a_topic);
    eprosima::fastdds::dds::DataReaderQos rqos = eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT;
    rqos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;
    return m_subscriber->create_datareader(a_topic, rqos, this);
}

ServiceSubscriber::~ServiceSubscriber()
{
    for  (auto reader: m_topicReaders)
    {
        m_subscriber->delete_datareader(reader);
    }
    if (m_subscriber != nullptr)
    {
        m_paritcipant->delete_subscriber(m_subscriber);
    }
    for (auto topic : topics)
    {
        m_paritcipant->delete_topic(topic);
    }
}

void ServiceSubscriber::on_subscription_matched(
    eprosima::fastdds::dds::DataReader* reader,
    const eprosima::fastdds::dds::SubscriptionMatchedStatus& info)
{
    if (n_matched < info.total_count)
    {
        std::cout << "Subscriber matched for DataReader: " << reader << std::endl;
    }
    else if (n_matched > info.total_count)
    {
        std::cout << "Subscriber unmatched for DataReader: " << reader << std::endl;
    }
    n_matched = info.total_count;
}

void ServiceSubscriber::on_data_available(eprosima::fastdds::dds::DataReader* reader)
{
    eprosima::fastdds::dds::SampleInfo info;


    if (reader->get_topicdescription()->get_name() == "prop_propInt")
    {
        HelloWorld l_message;
        l_message.index(0);
        l_message.message("empty");
        if (reader->take_next_sample(&l_message, &info) == ReturnCode_t::RETCODE_OK)
        {
            std::cout << "Received property changed REQ int: " << l_message.index() << std::endl;
            m_api->setPropInt(l_message.index());
        }
    }
}

