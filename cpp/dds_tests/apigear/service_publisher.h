#pragma once


#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>

#include "../HelloWorldPubSubTypes.h"

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <iostream>
#include <memory>

#include "../HelloWorld.h"
namespace ApiGear {

    namespace Utilities {
        class ThreadPool;
    }
}


class ServicePublisher :public eprosima::fastdds::dds::DataWriterListener
{
public:
    ServicePublisher(eprosima::fastdds::dds::DomainParticipant* participant);
    ~ServicePublisher();
    eprosima::fastdds::dds::DataWriter* createTopicPublisher(std::string topic, std::string dataType);
    bool isReady();
    void init();
    void run(uint32_t samples, uint32_t sleep);
    bool publishProp(int value);
    bool publishSig(int value);
private:
    eprosima::fastdds::dds::DomainParticipant* m_participant;
    void on_publication_matched(eprosima::fastdds::dds::DataWriter* writer, const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;
    int n_matched = 0;
    bool firstConnected = false;
    eprosima::fastdds::dds::Publisher* mp_publisher = nullptr;
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_requests_pool;

    std::vector< eprosima::fastdds::dds::Topic*> topics;
    //TODO temporaray public, should be stored privetly in map, and some getter should be given, or just returning a callback;
    eprosima::fastdds::dds::DataWriter* m_propertyChangedWriter = nullptr;
    eprosima::fastdds::dds::DataWriter* mp_singalEmitWriter = nullptr;
    // TODO this should be solved differently not as member
    HelloWorld hello_;
};