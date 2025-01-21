
#include "api/generated/mqtt/testapi0client.h"

#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include "../../latency_helpers/latency_helpers.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

#include <memory>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>


class PropertyIntTestData
{
public:
    PropertyIntTestData(std::shared_ptr<ApiGear::MQTT::Client> client,
        std::vector<chrono_hr_timepoint>& latenciesStart,
        std::vector<chrono_hr_timepoint>& latenciesStop)
        :m_latenciesStart(latenciesStart),
        m_latenciesStop(latenciesStop)
    {
        sink = std::make_shared<Cpp::Api::MQTT::TestApi0Client>(client);
        sink->_getPublisher().subscribeToPropIntChanged([this](int propInt)
            {
                if (propInt == 0)
                {
                    std::cout << "FIRST MSG";
                    return;
                }
                auto index = propInt-1;
                m_latenciesStop[index]=std::chrono::high_resolution_clock::now();
                count++;
            });
    }
    void testFunction(uint32_t value)
    {
        m_latenciesStart[value] = std::chrono::high_resolution_clock::now();
        sink->setPropInt(value +1);
        while (count < value){}
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return count == sentRequestsNumber;
    }

    bool isReady() const
    {
        return sink->_is_ready();
    }

    uint32_t receivedMessages() const
    {
        return count;
    }
private:
    std::vector<chrono_hr_timepoint>& m_latenciesStart;
    std::vector<chrono_hr_timepoint>& m_latenciesStop;

    std::atomic<uint32_t> count  { 0 };
    std::shared_ptr<Cpp::Api::MQTT::TestApi0Client> sink;
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

    std::string brokerUrl = "tcp://localhost:1883";
    MqttHandlerForTest networkProtocolHandler(brokerUrl);
    auto total_messages_number = messages_number * sendThreadNumber;
    std::vector<chrono_hr_timepoint> m_latenciesStart(total_messages_number, chrono_hr_timepoint());
    std::vector<chrono_hr_timepoint> m_latenciesStop(total_messages_number, chrono_hr_timepoint());

    PropertyIntTestData testObject(networkProtocolHandler.getClient(), m_latenciesStart, m_latenciesStop);
    executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);
    networkProtocolHandler.getClient()->disconnect();
    calculateAndPrintLatencyParameters(m_latenciesStart, m_latenciesStop);
    
    return 0;
}