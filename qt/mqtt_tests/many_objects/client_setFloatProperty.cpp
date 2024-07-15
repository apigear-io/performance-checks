#include "../../scenario_templates/many_objects/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include "../helpers/itestsink.h"
#include "../helpers/prepare_test_data.h"
#include <memory>

struct PropertyFloatTestData
{
public:

    PropertyFloatTestData(std::shared_ptr<ITestSink> in_sink, std::function<void(float)> func):
        sink(in_sink),
        funcToExecute(func)
    {}

    void testFunction(float param)
    {
        funcToExecute(param);
    }

    bool isReady() const
    {
        return sink->isReady();
    }

    const QString objectName() const
    {
        return sink->objectName();
    }

    bool allResponsesReceived(uint32_t messages_number) const
    {
        return sink->allResponsesReceived(messages_number);
    }
private:
    std::shared_ptr<ITestSink> sink;
    std::function<void(float)> funcToExecute;
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
    QCoreApplication app(argc, argv);
    std::vector<uint16_t> timePerMessage;
    auto messages_number = 1000u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }

    quint16 portNumber = 1883;
    QString address = "localhost";
    MqttHandlerForTest networkProtocolHandler(address, portNumber);

    FloatPropertySetter setter;
    auto testData = getTestData<PropertyFloatTestData, FloatPropertySetter>(setter, networkProtocolHandler.getClient());

    auto clientThread = executeTestFunction(testData, networkProtocolHandler, messages_number);

    return app.exec();
}
