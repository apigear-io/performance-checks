#include "api/generated/nats/testapi0client.h"

#include "../helpers/nats_network_protocol_handler_for_test.hpp"
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
    PropertyIntTestData(std::shared_ptr<ApiGear::Nats::Client> client,
        std::vector<chrono_hr_timepoint>& latenciesStart,
        std::vector<chrono_hr_timepoint>& latenciesStop)
        :m_latenciesStart(latenciesStart),
        m_latenciesStop(latenciesStop)
    {
        sink = Cpp::Api::Nats::TestApi0Client::create(client);
    }

    void testFunction(uint32_t value)
    {
        m_latenciesStart[value] = std::chrono::high_resolution_clock::now();
        auto result = sink->funcInt(value);
        msgsReceived++;
        m_latenciesStop[result] = std::chrono::high_resolution_clock::now();
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return true;
    }
    bool isReady() const
    {
        return sink->_is_ready();
    }

    uint32_t receivedMessages() const
    {
        return msgsReceived;
    }

    std::vector<chrono_hr_timepoint>& m_latenciesStart;
    std::vector<chrono_hr_timepoint>& m_latenciesStop;
    std::vector<std::shared_future<void>> m_futures;
    std::atomic<int> msgsReceived{ 0 };
    std::shared_ptr<Cpp::Api::Nats::TestApi0Client> sink;
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
    std::string brokerUrl = "nats://localhost:4222";
    NatsHandlerForTest networkProtocolHandler(brokerUrl);

    auto total_messages_number = messages_number * sendThreadNumber;
    std::vector<chrono_hr_timepoint> m_latenciesStart(total_messages_number, chrono_hr_timepoint());
    std::vector<chrono_hr_timepoint> m_latenciesStop(total_messages_number, chrono_hr_timepoint());
    PropertyIntTestData testObject(networkProtocolHandler.getClient(), m_latenciesStart, m_latenciesStop);

    executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);

    calculateAndPrintLatencyParameters(m_latenciesStart, m_latenciesStop);
    return 0;
}