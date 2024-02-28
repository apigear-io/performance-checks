#include "../helpers/inspected_sink.h"
#include "api/generated/olink/testapi0client.h"

#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

#include <memory>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>

class PropertyIntTestData
{
public:
    PropertyIntTestData(std::vector<std::chrono::steady_clock::time_point>& latenciesStart,
        std::vector<std::chrono::steady_clock::time_point>& latenciesStop)
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
        while (count < value){}
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return count == sentRequestsNumber;
    }

    std::vector<std::chrono::steady_clock::time_point>& m_latenciesStart;
    std::vector<std::chrono::steady_clock::time_point>& m_latenciesStop;

    std::atomic<uint32_t> count  { 0 };
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
    auto messages_number = 10u;
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
    std::vector<std::chrono::steady_clock::time_point> m_latenciesStart(messages_number * sendThreadNumber, std::chrono::steady_clock::time_point());
    std::vector<std::chrono::steady_clock::time_point> m_latenciesStop(messages_number * sendThreadNumber, std::chrono::steady_clock::time_point());
    PropertyIntTestData testObject(m_latenciesStart, m_latenciesStop);
    executeTestFunction(testObject, olinkProtocolHandler, messages_number, sendThreadNumber);
    

    uint32_t sum = 0;
    uint32_t min = std::chrono::duration_cast<std::chrono::microseconds>(m_latenciesStop[0] - m_latenciesStart[0]).count();
    uint32_t max = 0;
    for (size_t i = 0; i < m_latenciesStart.size(); i++)
    {
        auto latency = std::chrono::duration_cast<std::chrono::microseconds>(m_latenciesStop[i] - m_latenciesStart[i]).count();
        sum = sum + latency;
        if (min > latency) { min = latency; }
        if (max < latency) { max = latency; }
    }
    auto mean = double(sum) / m_latenciesStart.size();

    std::cout << "Latency: mean " << std::fixed << std::setprecision(2) << mean << " max " <<max << " min " << min << std::endl;
    
    return 0;
}