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
    QCoreApplication app(argc, argv);
    std::vector<uint16_t> timePerMessage;
    auto messages_number = 3u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }

    quint16 portNumber = 1883;
    QString address = "localhost";
    MqttHandlerForTest networkProtocolHandler(address, portNumber);

    IntPropertySetter setter;
    auto testData = getTestData<PropertyIntTestData, IntPropertySetter>(setter, networkProtocolHandler.getClient());

    auto clientThread = executeTestFunction(testData, networkProtocolHandler, messages_number);

    return app.exec();
}
