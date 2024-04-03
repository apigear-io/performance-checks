#include "../helpers/test_sink.h"
#include "api/api/api.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/latency_helper.h"

#include <memory>
#include <vector>
#include <chrono>

class PropertyIntTestData
{
public:
    PropertyIntTestData(std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& latenciesStart,
                        std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& latenciesStop)
        :m_latenciesStart(latenciesStart),
        m_latenciesStop(latenciesStop)
    {
        sink = std::make_shared<TestSink>();
        sink->connect(sink.get(), &api::AbstractTestApi0::propIntChanged, [this](int propInt)
                                                               {
                                                                   m_latenciesStop[propInt-1]=std::chrono::high_resolution_clock::now();
                                                                   count++;
                                                               });
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return true;
    }
    std::shared_ptr<TestSink> sink;
    void testFunction(uint32_t value)
    {
        m_latenciesStart[value] = std::chrono::high_resolution_clock::now();
        // Add one, to avoid setting property to 0 as first call, 0 is default property and it won't be set for same value.
        sink->setPropInt(value + 1);
        while (count <= value){}
    }

    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& m_latenciesStart;
    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>& m_latenciesStop;

    std::atomic<uint32_t> count{0};
};

/*
By default test request property int change 1000 times from each of 100 threads.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 1;
    auto messages_number = 1;
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

    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> m_latenciesStart(messages_number * sendThreadNumber, std::chrono::time_point<std::chrono::high_resolution_clock>());
    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> m_latenciesStop(messages_number * sendThreadNumber, std::chrono::time_point<std::chrono::high_resolution_clock>());
    std::vector<uint32_t> m_latencies(messages_number * sendThreadNumber, 0);
    auto testObject = PropertyIntTestData(m_latenciesStart, m_latenciesStop);

    auto calculate_latency = [&m_latenciesStart, &m_latenciesStop](){
        calculateAndPrintLatencyParameters(m_latenciesStart, m_latenciesStop);
    };

    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber, calculate_latency);

    return app.exec();
}
