#include "../helpers/test_sink.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/methodpropertyinttestdata.h"
#include "../helpers/latency_helper.h"

#include <memory>
#include <vector>
#include <chrono>

/*
By default test request property int change 100 times from each of 1 thread.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 1u;
    auto messages_number = 100u;
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
    OLinkHandlerForTest networkProtocolHandler(hostAddress, portNumber);

    std::vector<uint32_t> latencies(messages_number*sendThreadNumber,0u);
    auto testObject = SyncMethodPropertyIntTestData(latencies);

    auto calculateLatencies = [&latencies]()
    {
        calculateAndPrintLatencyParameters(latencies);
    };
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber, calculateLatencies);

    return app.exec();
}
