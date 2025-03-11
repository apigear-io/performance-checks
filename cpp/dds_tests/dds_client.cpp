#include "dds_client.h"

#include <fastrtps/Domain.h>
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
#include "types/HelloWorldPubSubTypes.h"
#include "types/samplePubSubTypes.h"

#include <thread>
using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
using namespace Cpp::Api;

TestApiClient::TestApiClient(std::string name)
{
    eprosima::fastdds::dds::DomainParticipantQos participant_qos = eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT;
    participant_qos.name(name);
    mp_participant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, participant_qos);

    if (mp_participant == nullptr)
    {
        std::cerr << "Failed to create DomainParticipant!" << std::endl;
        return;
    }

    m_types.push_back(static_cast<eprosima::fastdds::dds::TypeSupport>(new HelloWorldPubSubType()));
    m_types.push_back(static_cast<eprosima::fastdds::dds::TypeSupport>(new samplePubSubType()));
    for (auto type : m_types)
    {
        type.register_type(mp_participant);
    }

    m_ClientPublisher = std::make_unique<ClientPublisher>(mp_participant);
    m_ClientSubscriber = std::make_unique<ClientSubscriber>(mp_participant);

}

TestApiClient::~TestApiClient()
{
    m_ClientPublisher.reset();
    m_ClientSubscriber.reset();
    mp_participant->delete_contained_entities();
    if (mp_participant)
    {
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(mp_participant);
    }
}


void TestApiClient::init()
{
    m_ClientPublisher->init();
    m_ClientSubscriber->init();
    m_ClientPublisher->run(10, 200);
}

void TestApiClient::requestPropertyChange(int value) {
    m_ClientPublisher->publish(value);
}
void TestApiClient::remoteMethodCall(int value)
{
    if (m_ClientPublisher->_is_ready())
    {
        auto id = m_ClientPublisher->request_funcInt(value);
        m_ClientSubscriber->_add_pending_call_id(id);
    }
}