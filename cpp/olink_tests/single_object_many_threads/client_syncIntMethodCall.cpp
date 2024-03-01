#include "../helpers/inspected_sink.h"
#include "api/generated/olink/testapi0client.h"

#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/latency_helpers.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

#include <memory>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>

class PropertyIntTestData
{
public:
    PropertyIntTestData(std::vector<uint32_t>& latencies)
        :m_latencies(latencies)
    {
        olinkClient = std::make_shared<Cpp::Api::olink::TestApi0Client>();
        sink = std::make_shared<InspectedSink>(olinkClient);
    }
    void testFunction(uint32_t value)
    {
        auto start = std::chrono::high_resolution_clock::now();
        olinkClient->funcInt(value);
        auto end = std::chrono::high_resolution_clock::now();

        m_latencies[value] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return true;
    }

    std::vector<uint32_t>& m_latencies;
    std::shared_ptr<Cpp::Api::olink::TestApi0Client> olinkClient;
    std::shared_ptr<InspectedSink> sink;
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
    std::vector<uint32_t> latencies(messages_number*sendThreadNumber,0);
    auto testObject = PropertyIntTestData(latencies);

    executeTestFunction(testObject, olinkProtocolHandler, messages_number, sendThreadNumber);

    calculateAndPrintLatencyParameters(latencies);
    return 0;
}