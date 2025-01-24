#include "api/generated/mqtt/testapi0client.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../mqtt_network_protocol_handler_for_test.hpp"
#include <memory>


struct PropertyStringTestData
{
public:

    PropertyStringTestData(std::shared_ptr<ApiGear::MQTT::Client> client, uint32_t messages_number, uint32_t sendThreadNumber)
    {
        sink = std::make_shared<Cpp::Api::MQTT::TestApi0Client>(client);
        sink->_getPublisher().subscribeToPropStringChanged([this](auto value)
            {
                (void)value;
                count++;
            });
        for (int msgNo = 0u; msgNo < sendThreadNumber*(messages_number +1); msgNo++)
        {
            auto message = "Some longer property to be set, prepared before test for each message number to reduce allocating time in tests"+ std::to_string(msgNo);
            messagesToSend.push_back(message);
        }
    }

    void testFunction(uint32_t value)
    {
        sink->setPropString(messagesToSend[value]);
    }

    bool allResponsesReceived(uint32_t sentRequestsNumber) const
    {
        return count == sentRequestsNumber;
    }

    bool isReady() const
    {
        return sink->_is_ready();
    }

    uint32_t receivedMessages() const
    {
        return count;
    }

private:
    std::atomic<uint32_t> count{ 0 };
    std::shared_ptr<Cpp::Api::MQTT::TestApi0Client> sink;
    // Prepare different messages to send before test starts not to slow down it with allocation of this many messages:
    std::vector<std::string> messagesToSend;

};


/*
By default test request property string change 600 times from each of 100 threads.
Each message is over 100 character long.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 100u;
    auto messages_number = 1000u;
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

    std::string brokerUrl = "tcp://localhost:1883";
    MqttHandlerForTest networkProtocolHandler(brokerUrl);

    PropertyStringTestData testObject(networkProtocolHandler.getClient(), messages_number,sendThreadNumber);
    executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);
    networkProtocolHandler.getClient()->disconnect();
}

