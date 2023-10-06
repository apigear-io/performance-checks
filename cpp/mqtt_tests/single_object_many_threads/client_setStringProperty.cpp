#include "api/generated/mqtt/testapi0client.h"
#include "../helpers/itestsink.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include <memory>


class PropertyIntTestData
{
public:
    PropertyIntTestData(std::shared_ptr<ApiGear::MQTT::Client> client)
    {
        auto obj = std::make_shared<TestSink<Cpp::Api::MQTT::TestApi0Client>>(client);
        m_testFunction = [obj](uint32_t value)
        {
            // Add one, to avoid setting property to 0 as first call, 0 is default property and it won't be set for same value.
            obj->setPropInt(value + 1);
        };
        sink = obj;
    }

    void testFunction(uint32_t value)
    {
        m_testFunction(value);
    }

public:
    std::function<void(uint32_t)> m_testFunction;
    std::shared_ptr<ITestSink> sink;
};
struct PropertyStringTestData
{
public:

    PropertyStringTestData(std::shared_ptr<ApiGear::MQTT::Client> client, uint32_t messages_number, uint32_t sendThreadNumber)
    {
        for (int msgNo = 0u; msgNo < sendThreadNumber*(messages_number +1); msgNo++)
        {
            auto message = "Some longer property to be set, prepared before test for each message number to reduce allocating time in tests"+ std::to_string(msgNo);
            messagesToSend.push_back(message);
        }

        auto obj =  std::make_shared<TestSink<Cpp::Api::MQTT::TestApi0Client>>(client);
        m_testFunction = [obj, this](uint32_t value)
        {
            obj->setPropString(messagesToSend[value]);
        };
        sink = obj;

    }

    void testFunction(uint32_t value)
    {
        m_testFunction(value);
    }
    std::shared_ptr<ITestSink> sink;
private:
    std::function<void(uint32_t)> m_testFunction;
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

