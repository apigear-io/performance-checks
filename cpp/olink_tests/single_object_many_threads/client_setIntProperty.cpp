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
    PropertyIntTestData(std::vector<chrono_hr_timepoint>& latenciesStart,
                        std::vector<chrono_hr_timepoint>& latenciesStop)
        :m_latenciesStart(latenciesStart),
        m_latenciesStop(latenciesStop)
    {
        olinkClient = std::make_shared<Cpp::Api::olink::TestApi0Client>();
        sink = std::make_shared<InspectedSink>(olinkClient);
        olinkClient->_getPublisher().subscribeToPropIntChanged([this](int propInt) 
            {
                auto index = propInt-1;
                m_latenciesStop[index]=std::chrono::high_resolution_clock::now();
                count++;
            });
    }
    void testFunction(uint32_t value)
    {
        m_latenciesStart[value] = std::chrono::high_resolution_clock::now();
        olinkClient->setPropInt(value +1);
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return count == sentRequestsNumber;
    }

    std::vector<chrono_hr_timepoint>& m_latenciesStart;
    std::vector<chrono_hr_timepoint>& m_latenciesStop;

    uint32_t count=0;
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
    OLinkHandlerForTest olinkProtocolHandler(hostAddress, portNumber);

    std::vector<chrono_hr_timepoint> m_latenciesStart(messages_number * sendThreadNumber, std::chrono::steady_clock::time_point());
    std::vector<chrono_hr_timepoint> m_latenciesStop(messages_number * sendThreadNumber, std::chrono::steady_clock::time_point());

    auto testObject = PropertyIntTestData(m_latenciesStart, m_latenciesStop);
    executeTestFunction(testObject, olinkProtocolHandler, messages_number, sendThreadNumber);
    
    calculateAndPrintLatencyParameters(m_latenciesStart, m_latenciesStop);

    return 0;
}