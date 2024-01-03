#include "../helpers/itestsink.h"
#include "api/generated/mqtt/testapi0client.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"

#include <memory>


class PropertyIntTestData
{
public:
    PropertyIntTestData(std::shared_ptr<ApiGear::MQTT::Client> client)
    {
        auto obj =  std::make_shared<TestSink<Cpp::Api::MQTT::TestApi0Client>>(client);
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

/*
By default test request property int change 1000 times from each of 100 threads.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    auto sendThreadNumber = 100u;
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

    std::string brokerUrl = "tcp://localhost:1883";
    MqttHandlerForTest networkProtocolHandler(brokerUrl);

    PropertyIntTestData testObject(networkProtocolHandler.getClient());
    executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);
    networkProtocolHandler.getClient()->disconnect();
}

