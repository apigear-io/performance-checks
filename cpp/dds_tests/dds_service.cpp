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

#include <thread>
using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;


TestApi0Service::SubListener::SubListener(eprosima::fastdds::dds::DomainParticipant* paritcipant, std::shared_ptr< Cpp::Api::ITestApi0> api)
    : m_paritcipant(paritcipant),
    m_api(api),
    n_matched(0)
{
}

TestApi0Service::SubListener::~SubListener()
{
    if (mp_onMethodReqSub != nullptr)
    {
        m_subscriber->delete_datareader(mp_onMethodReqSub);
    }
    if (mp_onReqPropertyIntSub != nullptr)
    {
        m_subscriber->delete_datareader(mp_onReqPropertyIntSub);
    }
    if (m_subscriber != nullptr)
    {
        m_paritcipant->delete_subscriber(m_subscriber);
    }
    for (auto topic : topics)
    {
        m_paritcipant->delete_topic(topic);
    }
}

void TestApi0Service::SubListener::init()
{
    m_subscriber = m_paritcipant->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);
    createTopicSubscriber(mp_onReqPropertyIntSub, "prop.propInt", "HelloWorld");
    createTopicSubscriber(mp_onMethodReqSub, "rpc.funcInt", "HelloWorld"); //TODO WHAT WITH CLIENT ID
}

void TestApi0Service::SubListener::on_subscription_matched(
    eprosima::fastdds::dds::DataReader* reader,
    const eprosima::fastdds::dds::SubscriptionMatchedStatus& info)
{
    if (n_matched < info.total_count)
    {
        std::cout << "Subscriber matched for DataReader: " << reader << std::endl;
    }
    else if (n_matched > info.total_count)
    {
        std::cout << "Subscriber unmatched for DataReader: " << reader << std::endl;
    }
    n_matched = info.total_count;
}

void TestApi0Service::SubListener::on_data_available(eprosima::fastdds::dds::DataReader* reader)
{
    eprosima::fastdds::dds::SampleInfo info;

    if (reader == mp_onReqPropertyIntSub)
    {
        HelloWorld message;
        if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK && info.valid_data)
        {
            std::cout << "Received property changed REQ int: " << message.index() << std::endl;
            m_api->setPropInt(message.index());
        }
    }

    else if (reader == mp_onMethodReqSub)
    {
        HelloWorld message;
        if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK && info.valid_data)
        {
            std::cout << "Received sub REQ: " << message.index() << std::endl;
            m_api->funcInt(message.index());
            // SHOULD SEND A RESPONSE
        }
    }
}
void TestApi0Service::SubListener::createTopicSubscriber(eprosima::fastdds::dds::DataReader* reader, std::string topic, std::string dataType)
{
    eprosima::fastdds::dds::Topic* a_topic = m_paritcipant->create_topic(topic, dataType, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
    topics.push_back(a_topic);
    reader = m_subscriber->create_datareader(a_topic, eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT, this);
}


void TestApi0Service::PubListener::on_publication_matched(eprosima::fastdds::dds::DataWriter* writer, const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{
    if (n_matched < info.total_count)
    {
        std::cout << "Publisher matched." << std::endl;
        firstConnected = true;
    }
    else if (n_matched > info.total_count)
    {
        std::cout << "Publisher unmatched." << std::endl;
    }
    n_matched = info.total_count;
    //TODO check if matched for all topics!
}
//---------------------------------------
TestApi0Service::TestApi0Service(std::shared_ptr< Cpp::Api::ITestApi0> api)
    : m_api(api)
{
    m_api->_getPublisher().subscribeToAllChanges(*this);
    eprosima::fastdds::dds::DomainParticipantQos participant_qos;
    participant_qos.name("cpp.TestApi0service");
    eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Kind::Info);
    mp_participant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(7, participant_qos);

    if (mp_participant == nullptr)
    {
        std::cerr << "Failed to create DomainParticipant!" << std::endl;
        return;
    }

    m_helloType = eprosima::fastdds::dds::TypeSupport(new HelloWorldPubSubType());
    m_helloType.register_type(mp_participant);

    mp_publisher = mp_participant->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT);
    if (mp_publisher == nullptr)
    {
        std::cerr << "Failed to create Publisher!" << std::endl;
    }

}

TestApi0Service::~TestApi0Service()
{
    if (mp_signalIntWriter != nullptr)
    {
        mp_publisher->delete_datawriter(mp_signalIntWriter);
    }
    if (m_propertyChangedWriter != nullptr)
    {
        mp_publisher->delete_datawriter(m_propertyChangedWriter);
    }
    if (mp_publisher != nullptr)
    {
        mp_participant->delete_publisher(mp_publisher);
    }
    for (auto topic : topics)
    {
        mp_participant->delete_topic(topic);
    }
    if (mp_participant)
    {
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(mp_participant);
    }
}



eprosima::fastdds::dds::DataWriter* TestApi0Service::createTopicPublisher(std::string topic, std::string dataType)
{

    eprosima::fastdds::dds::Topic* topic_obj = mp_participant->create_topic(topic, dataType, eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
    if (!topic_obj)
    {
        std::cerr << "Failed to create Topic: " << topic << std::endl;
        return nullptr;
    }
    topics.push_back(topic_obj);

    eprosima::fastdds::dds::DataWriterQos writer_qos;
    writer_qos.reliability().kind = RELIABLE_RELIABILITY_QOS;

    return mp_publisher->create_datawriter(topic_obj, writer_qos, &m_publistener);
}

bool TestApi0Service::init()
{
    if (mp_participant == nullptr || mp_publisher == nullptr)
    {
        return false;
    }

    m_sublistener = std::make_unique<SubListener>(mp_participant, m_api);
    m_sublistener->init();
    m_propertyChangedWriter = createTopicPublisher("set.propInt", "HelloWorld");
    mp_signalIntWriter = createTopicPublisher("sig.sigInt", "HelloWorld");
    m_requests_pool = std::make_unique<ApiGear::Utilities::ThreadPool>(1);

    return m_propertyChangedWriter != nullptr && mp_signalIntWriter != nullptr;

}


void TestApi0Service::onPropIntChanged(int value) {
    if (m_publistener.isReady())
    {
        m_requests_pool->enqueue([this, value]()
            {
                hello_.index(value);
                hello_.message("prop");
                m_propertyChangedWriter->write(&hello_);
            });
    }
    // else LOG NOT CONNECTED, not ready
}
void TestApi0Service::onSigInt(int value)
{
    if (m_publistener.isReady())
    {
        m_requests_pool->enqueue([this, value]()
            {
                hello_.index(value);
                hello_.message("sig");
                mp_signalIntWriter->write(&hello_);
            });
    }
// else LOG NOT CONNECTED, not ready
}

