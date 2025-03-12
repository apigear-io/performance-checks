#pragma once


#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>

#include "../types/HelloWorldPubSubTypes.h"

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

#include "../types/HelloWorld.h"
#include "../types/sample.h"


namespace ApiGear {

    namespace Utilities {
        class ThreadPool;
    }
}

class IMethodResonder
{
public:
    virtual void sendResp_funcInt(Sample reply, eprosima::fastrtps::rtps::WriteParams params) = 0;
};


class ServicePublisher :public eprosima::fastdds::dds::DataWriterListener, public IMethodResonder
{
public:
    ServicePublisher(eprosima::fastdds::dds::DomainParticipant* participant);
    ~ServicePublisher();
    void init();
    bool publishProp(int value);
    bool publishSig(int value);
    bool _is_ready();
    void sendResp_funcInt(Sample reply, eprosima::fastrtps::rtps::WriteParams params) override;
private:
    eprosima::fastdds::dds::DataWriter* createTopicPublisher(std::string topic, std::string dataType);
    eprosima::fastdds::dds::DomainParticipant* m_participant;
    void on_publication_matched(eprosima::fastdds::dds::DataWriter* writer, const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;

    eprosima::fastdds::dds::Publisher* mp_publisher = nullptr;
    std::unique_ptr<ApiGear::Utilities::ThreadPool> m_requests_pool;

    std::vector< eprosima::fastdds::dds::Topic*> topics;
    eprosima::fastdds::dds::DataWriter* m_propertyChangedWriter = nullptr;
    eprosima::fastdds::dds::DataWriter* mp_singalEmitWriter = nullptr;
    eprosima::fastdds::dds::DataWriter* m_funcIntRespWriter = nullptr;
    std::map<std::string, bool> topics_matched;
};