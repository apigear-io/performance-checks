#pragma once


#include "HelloWorldPubSubTypes.h"
#include "api/generated/api/api.h"
#include "HelloWorldSubscriber.h"

#include "HelloWorldPubSubTypes.h"


#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <iostream>

#include "HelloWorld.h"
#include "apigear/service_subscriber.h"
#include "apigear/service_publisher.h"


class TestApi0Service : public Cpp::Api::ITestApi0Subscriber
{

public:

    TestApi0Service(std::shared_ptr< Cpp::Api::ITestApi0> api);
    virtual ~TestApi0Service();
    void init();


    void onSigInt(int paramInt) override;
    void onPropIntChanged(int propInt) override;
    void onSigFloat(float paramFloat) override {};
    void onSigString(const std::string& paramString) override {};
    void onPropFloatChanged(float propFloat) override {};
    void onPropStringChanged(const std::string& propString) override {};

private:

    std::unique_ptr<ServiceSubscriber> m_ServiceSubscriber;
    std::unique_ptr<ServicePublisher> m_ServicePublisher;

    std::shared_ptr< Cpp::Api::ITestApi0> m_api;
    eprosima::fastdds::dds::TypeSupport m_helloType;
    eprosima::fastdds::dds::DomainParticipant* mp_participant = nullptr;
};