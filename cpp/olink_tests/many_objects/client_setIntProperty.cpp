#include "../../scenario_templates/many_objects/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/inspected_sink.h"
#include "../helpers/prepare_test_data.h"


struct PropertyIntTestData
{
public:
    std::shared_ptr<InspectedSink> sink;
    std::function<void(int)> testFunction;
};

class IntPropertySetter {
public:
    template<class Interface>
    void testFunction(std::shared_ptr<Interface> object, int value)
    {
        object->setPropInt(value + 1);
    }
};

int main(int argc, char* argv[])
{
    auto messages_number = 1000u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }

    auto portNumber = 8000;
    auto hostAddress = "127.0.0.1";
    OLinkHandlerForTest olinkProtocolHandler(hostAddress, portNumber);

    IntPropertySetter setter;
    auto testData = getTestData<PropertyIntTestData, IntPropertySetter>(setter);

    executeTestFunction(testData, olinkProtocolHandler, messages_number);

    return 0;
}