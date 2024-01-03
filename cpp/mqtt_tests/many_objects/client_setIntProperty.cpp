#include "../../scenario_templates/many_objects/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include "../helpers/itestsink.h"
#include "../helpers/prepare_test_data.h"
#include <memory>

struct PropertyIntTestData
{
public:
    std::shared_ptr<ITestSink> sink;
    std::function<void(int)> testFunction;
};

class IntPropertySetter {
public:
    template<class Interface>
    void testFunction(std::shared_ptr<Interface> object, int value)
    {
        object->setPropInt(value);
    }
};



int main(int argc, char* argv[])
{
    std::vector<uint16_t> timePerMessage;
    auto messages_number = 500u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }

    std::string brokerUrl = "tcp://localhost:1883";
    MqttHandlerForTest networkProtocolHandler(brokerUrl);

    IntPropertySetter setter;
    auto testData = getTestData<PropertyIntTestData, IntPropertySetter>(setter, networkProtocolHandler.getClient());

    executeTestFunction(testData, networkProtocolHandler, messages_number);
    networkProtocolHandler.getClient()->disconnect();
}
