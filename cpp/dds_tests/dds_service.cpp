#include "dds_service.h"

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

#include <thread>
using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;


TestApi0Service::TestApi0Service(std::shared_ptr< Cpp::Api::ITestApi0> api)
    : m_api(api),
     m_helloType(new HelloWorldPubSubType())
{
    m_api->_getPublisher().subscribeToAllChanges(*this);

    eprosima::fastdds::dds::DomainParticipantQos participant_qos = eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT;
    participant_qos.name("sTA0");
    //eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Kind::Info);
    mp_participant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, participant_qos);
    if (mp_participant == nullptr)
    {
        std::cerr << "Failed to create DomainParticipant!" << std::endl;
        return;
    }
    m_helloType.register_type(mp_participant);

    m_ServiceSubscriber = std::make_unique<ServiceSubscriber>(mp_participant, m_api);
    m_ServicePublisher = std::make_unique<ServicePublisher>(mp_participant);

}

TestApi0Service::~TestApi0Service()
{
    if (mp_participant)
    {
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(mp_participant);
    }
}

void TestApi0Service::init()
{
    m_ServicePublisher->init();
    m_ServiceSubscriber->init();
}


void TestApi0Service::onPropIntChanged(int value) 
{
    std::cout << "sending prop " << value << std::endl;
    m_ServicePublisher->publishProp(value);
}
void TestApi0Service::onSigInt(int value)
{
    std::cout << "sending sig " << value << std::endl;
    m_ServicePublisher->publishSig(value);
}

