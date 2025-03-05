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

namespace {
    void fill_topics_matched(std::map<std::string, bool>& map_to_fill)
    {
        map_to_fill["prop_propInt"] = false;
    }
}

ServiceSubscriber::ServiceSubscriber(eprosima::fastdds::dds::DomainParticipant* paritcipant, std::shared_ptr< Cpp::Api::ITestApi0> api)
    : m_paritcipant(paritcipant),
    m_api(api)
{
    m_subscriber = m_paritcipant->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);
}
void ServiceSubscriber::init() 
{
    fill_topics_matched(topics_matched);
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

bool ServiceSubscriber::_is_ready()
{
    bool all_matched = std::find_if(topics_matched.begin(), topics_matched.end(), [](auto& element) {return element.second == false; })
        == topics_matched.end();
    return topics_matched.size() > 0 && all_matched;
}

void ServiceSubscriber::on_subscription_matched(
    eprosima::fastdds::dds::DataReader* reader,
    const eprosima::fastdds::dds::SubscriptionMatchedStatus& info)
{
    auto element = topics_matched.find(reader->get_topicdescription()->get_name());
    if (element == topics_matched.end())
    {
        //TODO log unexpected topic
        return;
    }
    element->second = info.current_count != 0;

    if (info.current_count_change > 0)
    {
        std::cout << "Subscriber matched." << element->first << std::endl;
    }
    else if (info.current_count_change < 0)
    {
        std::cout << "Subscriber unmatched." << element->first << std::endl;
    }
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

