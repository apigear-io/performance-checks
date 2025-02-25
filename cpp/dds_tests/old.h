#include <memory>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "fastdds/dds/builtin/common/ReplyHeader.hpp"
#include "fastdds/dds/builtin/common/RequestHeader.hpp"
#include "fastdds/dds/builtin/common/Types.hpp"
#include "fastdds/dds/builtin/topic/BuiltinTopicKey.hpp"
#include "fastdds/dds/builtin/topic/ParticipantBuiltinTopicData.hpp"
#include "fastdds/dds/builtin/topic/PublicationBuiltinTopicData.hpp"
#include "fastdds/dds/builtin/topic/SubscriptionBuiltinTopicData.hpp"
#include "fastdds/dds/builtin/topic/TopicBuiltinTopicData.hpp"
#include "fastdds/dds/builtin/typelookup/TypeLookupManager.hpp"
#include "fastdds/dds/builtin/typelookup/TypeLookupReplyListener.hpp"
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastrtps/Domain.h>

#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <vector>


// Define simple callback functions for subscription and publication match
void on_subscription_matched(eprosima::fastdds::dds::Subscriber* sub, eprosima::fastrtps::rtps::MatchingInfo& info)
{
    if (info.status == eprosima::fastrtps::rtps::MatchingStatus::MATCHED_MATCHING)
    {
        std::cout << "Subscriber matched with: " << info.remoteEndpointGuid << std::endl;
    }
    else
    {
        std::cout << "Subscriber unmatched with: " << info.remoteEndpointGuid << std::endl;
    }
}

void on_publication_matched(eprosima::fastdds::dds::Publisher* pub, eprosima::fastrtps::rtps::MatchingInfo& info)
{
    if (info.status == eprosima::fastrtps::rtps::MatchingStatus::MATCHED_MATCHING)
    {
        std::cout << "Publisher matched with: " << info.remoteEndpointGuid << std::endl;
    }
    else
    {
        std::cout << "Publisher unmatched with: " << info.remoteEndpointGuid << std::endl;
    }
}


// Function to create a participant with a partition
eprosima::fastdds::dds::DomainParticipant* create_participant(const std::string& partition_name)
{
    eprosima::fastdds::dds::DomainParticipantQos pqos;

    eprosima::fastdds::dds::DomainParticipant* participant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, pqos);

    if (!participant) {
        std::cerr << "Failed to create participant!" << std::endl;
        return nullptr;
    }

    // Create Publisher with Partition
    eprosima::fastdds::dds::PublisherQos pub_qos;
    pub_qos.partition().push_back(partition_name.c_str());
    eprosima::fastdds::dds::Publisher* publisher = eprosima::fastrtps::Domain::createPublisher(participant, pub_qos, on_publication_matched);

    // Create Subscriber with Partition
    eprosima::fastdds::dds::SubscriberQos sub_qos;
    sub_qos.partition().push_back(partition_name.c_str());
    eprosima::fastdds::dds::Subscriber* subscriber = eprosima::fastrtps::Domain::createSubscriber(participant, sub_qos, on_subscription_matched);


    return participant;
}
//-----------------------------------------------------------------------------------------------------------
// 
// For there should be a header with simple types.
// For custom structures we'll have MyStructMessage
// For signals we need MySignalMessage with all the params
// For invoke we need MyMethod with call id and params
// For invoker resps we should probably have simpleTypeResps -> simple type + id
//                                           MyStructResp with struct and id (or some kind wrapper that adds an id)


// Custom listener for acknowledgments
class PubListener : public eprosima::fastdds::dds::DataWriterListener
{
public:
    void on_publication_matched(eprosima::fastdds::dds::DataWriter*, const eprosima::fastdds::dds::PublicationMatchedStatus& info) override
    {
        if (info.current_count_change == 1)
            std::cout << "Publisher matched!\n";
    }
};

PubListener* createTestApiClientPubListener(eprosima::fastdds::dds::DomainParticipant* participant)
{

    // Create Publisher
    eprosima::fastdds::dds::Publisher* publisher = participant->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT);

    // Create two topics: "TopicA" and "TopicB"
    eprosima::fastdds::dds::Topic* topicA = participant->create_topic("TopicA", "Message", eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
    eprosima::fastdds::dds::Topic* topicB = participant->create_topic("TopicB", "Message", eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

    // Create DataWriter for each topic
    PubListener listener;
    eprosima::fastdds::dds::DataWriter* writerA = publisher->create_datawriter(topicA, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT, &listener);
    eprosima::fastdds::dds::DataWriter* writerB = publisher->create_datawriter(topicB, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT, &listener);

    // Send messages in a loop
    for (int i = 1; i <= 5; ++i)
    {
        Message msgA = { "Message " + std::to_string(i) + " to TopicA" };
        Message msgB = { "Message " + std::to_string(i) + " to TopicB" };

        // Serialize and publish
        eprosima::fastcdr::FastBuffer bufferA(reinterpret_cast<char*>(&msgA), sizeof(msgA));
        eprosima::fastcdr::Cdr serializerA(bufferA);
        msgA.serialize(serializerA);
        writerA->write(&msgA);

        eprosima::fastcdr::FastBuffer bufferB(reinterpret_cast<char*>(&msgB), sizeof(msgB));
        eprosima::fastcdr::Cdr serializerB(bufferB);
        msgB.serialize(serializerB);
        writerB->write(&msgB);

        std::cout << "Published: " << msgA.data << " | " << msgB.data << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------------------

// Custom listener to handle incoming messages
class SubListener : public eprosima::fastdds::dds::DataReaderListener
{
public:
    void on_data_available(eprosima::fastdds::dds::DataReader* reader) override
    {
        eprosima::fastdds::dds::SampleInfo info;
        Message msg;
        if (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK && info.valid_data)
        {
            std::cout << "Received: " << msg.data << std::endl;
        }
    }
};

std::shared_ptr<SubListener> createTestApiClientSubListener(eprosima::fastdds::dds::DomainParticipant* participant)
{

    // Create Subscriber
    eprosima::fastdds::dds::Subscriber* subscriber = participant->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT);

    // Create two topics: "TopicA" and "TopicB"
    eprosima::fastdds::dds::Topic* topicA = participant->create_topic("set.PropInt", "IntMessage", eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
    eprosima::fastdds::dds::Topic* topicB = participant->create_topic("set.PropString", "StringMessage", eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

    // Create DataReader for each topic
    auto listener = std::make_shared<SubListener>();
    eprosima::fastdds::dds::DataReader* readerA = subscriber->create_datareader(topicA, eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT, listener.get());
    eprosima::fastdds::dds::DataReader* readerB = subscriber->create_datareader(topicB, eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT, listener.get());

    return listener;
}
//-----------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 1u;
    auto messages_number = 10u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }
    if (argc > 2)
    {
        char* p;
        sendThreadNumber = strtol(argv[2], &p, 10);
    }

    eprosima::fastdds::dds::DomainParticipant* classA_participant = create_participant("cpp.TestApi0");
    eprosima::fastdds::dds::DomainParticipant* classB_participant = create_participant("cpp.TestApi0");

    return 0;
}