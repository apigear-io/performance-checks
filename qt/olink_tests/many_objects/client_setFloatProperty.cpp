#include "../../scenario_templates/many_objects/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/inspected_sink.h"
#include "../helpers/prepare_test_data.h"
#include <memory>

struct PropertyFloatTestData
{
public:
    std::shared_ptr<InspectedSink> sink;
    std::function<void(int)> testFunction;
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return sink->propertyChangedTimes() == sentRequestsNumber;
    }
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

    auto portNumber = 8000;
    auto hostAddress = "127.0.0.1";
    OLinkHandlerForTest olinkProtocolHandler(hostAddress, portNumber);
    FloatPropertySetter setter;
    auto testData = getTestData<PropertyFloatTestData, FloatPropertySetter>(setter);

    auto clientThread = executeTestFunction(testData, olinkProtocolHandler, messages_number);

    return app.exec();
}
