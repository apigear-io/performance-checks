#pragma once


#include "HelloWorldPubSubTypes.h"

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>

#include "HelloWorldPubSubTypes.h"

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

#include "HelloWorld.h"

namespace ApiGear {

    namespace Utilities {
        class ThreadPool;
    }
}

class TestApiClient
{
    class SubListener : public eprosima::fastdds::dds::DataReaderListener
    {
    public:

        SubListener(eprosima::fastdds::dds::DomainParticipant* paritcipant);

        ~SubListener();
        void createTopicSubscriber(eprosima::fastdds::dds::DataReader* topic_publisher, std::string topic, std::string dataType);
        void on_subscription_matched(eprosima::fastdds::dds::DataReader* reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;
        void on_data_available(eprosima::fastdds::dds::DataReader* reader) override;
        void init();

        int n_matched;
    private:
        std::vector< eprosima::fastdds::dds::Topic*> topics;
        eprosima::fastdds::dds::DomainParticipant* m_paritcipant;
        eprosima::fastdds::dds::Subscriber* m_subscriber = nullptr;
        eprosima::fastdds::dds::DataReader* mp_onPropertyIntChangedSub = nullptr;
        eprosima::fastdds::dds::DataReader* mp_sonSignalIntSub = nullptr;
        eprosima::fastdds::dds::DataReader* mp_onMethodRespSub = nullptr;
    };

    class PubListener :public eprosima::fastdds::dds::DataWriterListener
    {
    public:
        PubListener() :n_matched(0), firstConnected(false) {};
        ~PubListener() {};
        void on_publication_matched(eprosima::fastdds::dds::DataWriter* writer, const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;
        int n_matched;
        bool firstConnected;
    };



public:
    TestApiClient();
    virtual ~TestApiClient();
    bool init();

    void requestPropertyChange(int value);
    void remoteMethodCall(int value);
private:

    eprosima::fastdds::dds::DataWriter* createTopicPublisher(std::string topic, std::string dataType);

    eprosima::fastdds::dds::DomainParticipant* mp_participant = nullptr;
    eprosima::fastdds::dds::Publisher* mp_publisher = nullptr;
    eprosima::fastdds::dds::DataWriter* m_propertyChangedWriter = nullptr;
    eprosima::fastdds::dds::DataWriter* mp_methodWriter = nullptr;
    PubListener m_publistener;
    std::unique_ptr<SubListener> m_sublistener;
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_requests_pool;
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_sub_pool;
    eprosima::fastdds::dds::TypeSupport m_helloType;
    HelloWorld hello_;
    std::vector< eprosima::fastdds::dds::Topic*> topics;
};