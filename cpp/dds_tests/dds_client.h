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
#include "apigear/client_publisher.h"
#include "apigear/client_subscriber.h"
#include "api/generated/api/api.h"
#include "api/generated/core/testapi0.data.h"
#include "HelloWorldPublisher.h"
#include "HelloWorld.h"

namespace Cpp{

namespace Api {

class TestApiClient //: public Cpp::Api::ITestApi0
{
public:
    TestApiClient(std::string name);
    virtual ~TestApiClient();
    void init();

    void requestPropertyChange(int value);
    void remoteMethodCall(int value);
private:
    std::unique_ptr<ClientPublisher> m_ClientPublisher;
    std::unique_ptr<ClientSubscriber> m_ClientSubscriber;
    eprosima::fastdds::dds::TypeSupport m_helloType;
    eprosima::fastdds::dds::DomainParticipant* mp_participant = nullptr;

};
}
}