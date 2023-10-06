#include "test_sink.h"

#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

#include <memory>

class PropertyIntTestData
{
public:
    PropertyIntTestData()
    {
        sink = std::make_shared<TestSink>();
    }
    std::shared_ptr<TestSink> sink;
    void testFunction(uint32_t value)
    {
        sink->setPropInt(value + 1);
    }
};

/*
By default test request property int change 1000 times from each of 100 threads.
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
    auto portNumber = 8000;
    auto hostAddress = "127.0.0.1";
    OLinkHandlerForTest olinkProtocolHandler(hostAddress, portNumber);
    auto testObject = PropertyIntTestData();

    executeTestFunction(testObject, olinkProtocolHandler, messages_number, sendThreadNumber);
    
    return 0;
}