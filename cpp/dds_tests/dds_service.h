#pragma once


#include "HelloWorldPubSubTypes.h"
#include "api/generated/api/api.h"


#include "HelloWorldPubSubTypes.h"


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

class TestApi0Service : public Cpp::Api::ITestApi0Subscriber
{
    class SubListener : public eprosima::fastdds::dds::DataReaderListener
    {
    public:

        SubListener(eprosima::fastdds::dds::DomainParticipant* paritcipant, std::shared_ptr< Cpp::Api::ITestApi0> api);

        ~SubListener();
        void createTopicSubscriber(eprosima::fastdds::dds::DataReader* topic_publisher, std::string topic, std::string dataType);
        void on_subscription_matched(eprosima::fastdds::dds::DataReader* reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;
        void on_data_available(eprosima::fastdds::dds::DataReader* reader) override;
        void init();

        int n_matched;
    private:
        std::shared_ptr< Cpp::Api::ITestApi0> m_api;
        std::vector< eprosima::fastdds::dds::Topic*> topics;
        eprosima::fastdds::dds::DomainParticipant* m_paritcipant;
        eprosima::fastdds::dds::Subscriber* m_subscriber = nullptr;
        eprosima::fastdds::dds::DataReader* mp_onReqPropertyIntSub = nullptr;
        eprosima::fastdds::dds::DataReader* mp_onMethodReqSub = nullptr;
    };

    class PubListener :public eprosima::fastdds::dds::DataWriterListener
    {
    public:
        PubListener()
            :n_matched(0),
            firstConnected(false)
        {};
        ~PubListener() {};
        bool isReady() { return firstConnected || n_matched > 0; }
    private:
        void on_publication_matched(eprosima::fastdds::dds::DataWriter* writer, const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;
        int n_matched;
        bool firstConnected;
    };



public:


    TestApi0Service(std::shared_ptr< Cpp::Api::ITestApi0> api);
    virtual ~TestApi0Service();
    bool init();


    void onSigInt(int paramInt) override;
    void onPropIntChanged(int propInt) override;
    void onSigFloat(float paramFloat) override {};
    void onSigString(const std::string& paramString) override {};
    void onPropFloatChanged(float propFloat) override {};
    void onPropStringChanged(const std::string& propString) override {};

private:

    eprosima::fastdds::dds::DataWriter* createTopicPublisher(std::string topic, std::string dataType);

    eprosima::fastdds::dds::DomainParticipant* mp_participant = nullptr;
    eprosima::fastdds::dds::Publisher* mp_publisher = nullptr;
    eprosima::fastdds::dds::DataWriter* m_propertyChangedWriter = nullptr;
    eprosima::fastdds::dds::DataWriter* mp_signalIntWriter = nullptr;
    PubListener m_publistener;
    std::unique_ptr<SubListener> m_sublistener;
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_requests_pool;
    std::shared_ptr< Cpp::Api::ITestApi0> m_api;
    eprosima::fastdds::dds::TypeSupport m_helloType;
    std::vector< eprosima::fastdds::dds::Topic*> topics;
    HelloWorld hello_;
};