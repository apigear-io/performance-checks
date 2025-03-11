#include "api/generated/api/api.h"

#include "../types/HelloWorldPubSubTypes.h"

#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <iostream>
#include "api/generated/api/api.h"
#include "api/generated/core/testapi0.data.h"
#include <map>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/topic/ContentFilteredTopic.hpp>
#include <mutex>


#include "../types/HelloWorld.h"

class ClientSubscriber : public eprosima::fastdds::dds::DataReaderListener
{
public:

    ClientSubscriber(eprosima::fastdds::dds::DomainParticipant* paritcipant);
    void init();
    ~ClientSubscriber();
    void on_subscription_matched(eprosima::fastdds::dds::DataReader* reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

    std::shared_ptr<Cpp::Api::ITestApi0Publisher> getPublisher()
    {
        return m_publisher;
    }
    bool _is_ready();
    void _add_pending_call_id(eprosima::fastrtps::rtps::SampleIdentity);
private:
    eprosima::fastdds::dds::DataReader* createTopicSubscriber(std::string topic, std::string dataType);
    eprosima::fastdds::dds::DataReader* createFilteredTopicSubscriber(std::string topic, std::string dataType);

    void on_data_available(eprosima::fastdds::dds::DataReader* reader) override;
    std::vector< eprosima::fastdds::dds::Topic*> topics;
    eprosima::fastdds::dds::DomainParticipant* m_paritcipant;
    eprosima::fastdds::dds::Subscriber* m_subscriber = nullptr;
    std::vector<eprosima::fastdds::dds::DataReader*> m_topicReaders ;
    Cpp::Api::TestApi0Data m_data;
    std::shared_ptr<Cpp::Api::ITestApi0Publisher> m_publisher;
    std::map<std::string, bool> topics_matched;
    std::mutex calls_ids_mutex;
    std::vector<eprosima::fastrtps::rtps::SampleIdentity> pending_calls;

    std::vector<eprosima::fastdds::dds::ContentFilteredTopic*> filtered_topics;
    std::string m_topic_filter_expression;
    std::string m_filter_name_client_id;
    std::vector<std::string> reply_topic_filter_parameters_;
};