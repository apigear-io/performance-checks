#pragma once
#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "Generated/api/AbstractApiTestApi0.h"
#include "AbstractTestBase.h"
#include "Counter.h"

#include <memory>
#include <vector>
#include <chrono>
#include "AsyncIntMethodTest.generated.h"


UCLASS()
class UAsyncIntMethodTest : public UAbstractTestBase
{
    GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0, UCounter* counter, int requestsPerCall, int callsNumber)
    {

        m_clientApi0 = clientApi0;
        m_request_per_trhead = requestsPerCall;
        m_counter = counter;
        int messages_number = requestsPerCall * callsNumber;
        m_startTimePoints = std::vector<chrono_hr_timepoint>(messages_number, chrono_hr_timepoint());
        m_stopTimePoints = std::vector<chrono_hr_timepoint>(messages_number, chrono_hr_timepoint());
        m_futures = std::vector<TSharedFuture<void>>(messages_number, TSharedFuture<void>());
    }

    void cleanUp() override
    {
        for (auto& future : m_futures)
        {
            future.Get();
        }
    }

    void start(int startNumber) override
    {
        for (auto i = 0; i < m_request_per_trhead; i++)
        {
            auto number = startNumber + i;
            m_futures[number]=(Async(EAsyncExecution::Thread,
                [number, this]()
                {
                    m_startTimePoints[number] = std::chrono::high_resolution_clock::now();
                    m_clientApi0->Execute_FuncInt(m_clientApi0, number);
                    m_stopTimePoints[number] = std::chrono::high_resolution_clock::now();
                    m_counter->increaseInt(number);
                }).Share());
        }
    }
     UCounter* m_counter = nullptr;
private:
    UApiTestApi0OLinkClient* m_clientApi0;
    int m_request_per_trhead;
    std::vector<TSharedFuture<void>> m_futures;
};