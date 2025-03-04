#include "api/generated/api/api.h"

#include "../HelloWorldPubSubTypes.h"

#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <iostream>

#include "../HelloWorld.h"

class ServiceSubscriber : public eprosima::fastdds::dds::DataReaderListener
{
public:

    ServiceSubscriber(eprosima::fastdds::dds::DomainParticipant* paritcipant, std::shared_ptr< Cpp::Api::ITestApi0> api);
    void init();
    ~ServiceSubscriber();
    eprosima::fastdds::dds::DataReader* createTopicSubscriber(std::string topic, std::string dataType);
    void on_subscription_matched(eprosima::fastdds::dds::DataReader* reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

    int n_matched;
private:
    void on_data_available(eprosima::fastdds::dds::DataReader* reader) override;
    std::shared_ptr< Cpp::Api::ITestApi0> m_api;
    std::vector< eprosima::fastdds::dds::Topic*> topics;
    eprosima::fastdds::dds::DomainParticipant* m_paritcipant;
    eprosima::fastdds::dds::Subscriber* m_subscriber = nullptr;
    std::vector<eprosima::fastdds::dds::DataReader*> m_topicReaders ;
    HelloWorld message;
};