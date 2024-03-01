#include "../helpers/inspected_sink.h"
#include "api/generated/olink/testapi0client.h"

#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/latency_helpers.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

#include <memory>
#include <chrono>
#include <algorithm>
#include <future>
#include <iostream>
#include <iomanip>



class AsyncTestApi0ClientWrapper : public Cpp::Api::olink::TestApi0Client
{
public: 
    AsyncTestApi0ClientWrapper(std::function<void(int)> callback)
        : m_callback(callback)
    {}

    std::future<int> funcIntAsync(int paramInt) override
    {
        if(!getNode()) {
            return std::future<int>{};
        }
        return std::async(std::launch::async, [paramInt, this]()
            {
                std::promise<int> resultPromise;
                static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt");
                getNode()->invokeRemote(operationId,
                    nlohmann::json::array({paramInt}), [&resultPromise, this](ApiGear::ObjectLink::InvokeReplyArg arg) {
                        int value = arg.value.get<int>();
                        resultPromise.set_value(value);
                        if (m_callback)
                        {
                            m_callback(value);
                        }
                    });
                return resultPromise.get_future().get();
            }
        );
    }
    std::function<void(int)> m_callback;
};

class PropertyIntTestData
{
public:
    PropertyIntTestData(std::vector<chrono_hr_timepoint>& latenciesStart,
                        std::vector<chrono_hr_timepoint>& latenciesStop)
        :m_latenciesStart(latenciesStart),
        m_latenciesStop(latenciesStop)
    {
        m_futures = std::vector<std::shared_future<int>>(latenciesStart.size(), std::shared_future<int > ());
        auto callback = [this](int value)
        {
            if (value >= 0 && value < m_latenciesStop.size())
            {
                m_latenciesStop[value] = std::chrono::high_resolution_clock::now();
            }
            isAllReceived++;
        };
        olinkClient = std::make_shared<AsyncTestApi0ClientWrapper>(callback);
        sink = std::make_shared<InspectedSink>(olinkClient);
    }
    void testFunction(uint32_t value)
    {
        m_latenciesStart[value] = std::chrono::high_resolution_clock::now();

        auto task = olinkClient->funcIntAsync(value);
        m_futures[value]=task.share();
    }

    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return isAllReceived == sentRequestsNumber;
    }

    std::vector<chrono_hr_timepoint>& m_latenciesStart;
    std::vector<chrono_hr_timepoint>& m_latenciesStop;
    std::vector<std::shared_future<int>> m_futures;
    std::atomic<int> isAllReceived{ 0 };
    std::shared_ptr<AsyncTestApi0ClientWrapper> olinkClient;
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
    auto sendThreadNumber = 10u;
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

    std::vector<chrono_hr_timepoint> m_latenciesStart(messages_number * sendThreadNumber, std::chrono::steady_clock::time_point());
    std::vector<chrono_hr_timepoint> m_latenciesStop(messages_number * sendThreadNumber, std::chrono::steady_clock::time_point());
    PropertyIntTestData testObject(m_latenciesStart, m_latenciesStop);

    executeTestFunction(testObject, olinkProtocolHandler, messages_number, sendThreadNumber);
    
    calculateAndPrintLatencyParameters(m_latenciesStart, m_latenciesStop);

    return 0;
}