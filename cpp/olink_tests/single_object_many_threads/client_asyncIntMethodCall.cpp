#include "../helpers/inspected_sink.h"
#include "api/generated/olink/testapi0client.h"

#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../../latency_helpers/latency_helpers.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

#include <memory>
#include <chrono>
#include <algorithm>
#include <future>
#include <iostream>
#include <iomanip>


class PropertyIntTestData
{
public:
    PropertyIntTestData(std::vector<chrono_hr_timepoint>& latenciesStart,
                        std::vector<chrono_hr_timepoint>& latenciesStop)
        :m_latenciesStart(latenciesStart),
        m_latenciesStop(latenciesStop)
    {
        m_futures = std::vector<std::shared_future<int>>(latenciesStart.size(), std::shared_future<int>());
        olinkClient = std::make_shared<Cpp::Api::olink::TestApi0Client>();
        sink = std::make_shared<Cpp::Api::olink::TestApi0Client>();
    }
    void testFunction(uint32_t value)
    {
        m_latenciesStart[value] = std::chrono::high_resolution_clock::now();
        auto task = sink->funcIntAsync(value,
            [this](int32_t value) {
                m_latenciesStop[value] = std::chrono::high_resolution_clock::now();
                msgsReceived++;
            });

        m_futures[value] = task.share();
    }

    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return msgsReceived >= sentRequestsNumber;
    }

    std::vector<chrono_hr_timepoint>& m_latenciesStart;
    std::vector<chrono_hr_timepoint>& m_latenciesStop;
    std::vector<std::shared_future<int>> m_futures;
    std::shared_ptr< Cpp::Api::olink::TestApi0Client> olinkClient;
    std::atomic<int> msgsReceived{ 0 };
    std::shared_ptr<Cpp::Api::olink::TestApi0Client> sink;
};

/*
By default test request property int change 1000 times from each of 100 threads.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 1u;
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

    auto total_messages_number = messages_number * sendThreadNumber;
    std::vector<chrono_hr_timepoint> m_latenciesStart(total_messages_number, chrono_hr_timepoint());
    std::vector<chrono_hr_timepoint> m_latenciesStop(total_messages_number, chrono_hr_timepoint());
    PropertyIntTestData testObject(m_latenciesStart, m_latenciesStop);

    executeTestFunction(testObject, olinkProtocolHandler, messages_number, sendThreadNumber);
    
    calculateAndPrintLatencyParameters(m_latenciesStart, m_latenciesStop);

    return 0;
}