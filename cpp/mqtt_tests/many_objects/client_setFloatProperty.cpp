#include "../../scenario_templates/many_objects/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include "../helpers/itestsink.h"
#include "../helpers/prepare_test_data.h"
#include <memory>

struct PropertyFloatTestData
{
public:
    std::shared_ptr<ITestSink> sink;
    std::function<void(float)> testFunction;
};

class FloatPropertySetter {
public:
    template<class Interface>
    void testFunction(std::shared_ptr<Interface> object, float value)
    {
        object->setPropFloat(value);
    }
};

int main(int argc, char* argv[])
{
    std::vector<uint16_t> timePerMessage;
    auto messages_number = 1000u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }

    std::string brokerUrl = "tcp://localhost:1883";
    MqttHandlerForTest networkProtocolHandler(brokerUrl);

    FloatPropertySetter setter;
    auto testData = getTestData<PropertyFloatTestData, FloatPropertySetter>(setter, networkProtocolHandler.getClient());

    executeTestFunction(testData, networkProtocolHandler, messages_number);
    networkProtocolHandler.getClient()->disconnect();
}
