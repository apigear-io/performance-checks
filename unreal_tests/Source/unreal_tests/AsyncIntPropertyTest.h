#pragma once

#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "Generated/api/AbstractApiTestApi0.h"
#include "AbstractTestBase.h"
#include "Counter.h"

#include <memory>
#include <vector>
#include <chrono>

#include "AsyncIntPropertyTest.generated.h"

UCLASS()
class UNREAL_TESTS_API UAsyncIntPropertyTest : public UAbstractTestBase
{
	GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0, int requestsPerCall, int callsNumber)
    {
        m_clientApi0 = clientApi0;
        m_request_per_trhead = requestsPerCall;
        int messages_number = requestsPerCall * callsNumber;
        m_startTimePoints= std::vector<chrono_hr_timepoint>(messages_number, chrono_hr_timepoint());
        m_stopTimePoints =  std::vector<chrono_hr_timepoint>(messages_number, chrono_hr_timepoint());
        m_clientApi0->_GetSignals_Implementation()->OnPropIntChanged.AddDynamic(this, &UAsyncIntPropertyTest::AddStopTimePointPropertyInt);
    }

    void cleanUp() override
    {
        m_clientApi0->_GetSignals_Implementation()->OnPropIntChanged.RemoveDynamic(this, &UAsyncIntPropertyTest::AddStopTimePointPropertyInt);
    }

    void start(int startNumber) override
    {
        for (auto i = 0; i < m_request_per_trhead; i++)
        {
            auto number = startNumber + i;
            m_startTimePoints[number] = std::chrono::high_resolution_clock::now();
            m_clientApi0->Execute_SetPropInt(m_clientApi0, number+1);
        }
    }
    
    UFUNCTION()
    void AddStopTimePointPropertyInt(int number)
    {
        int index = number - 1;
        m_stopTimePoints[index] = std::chrono::high_resolution_clock::now();
    }
private:
    UApiTestApi0OLinkClient* m_clientApi0;
    int m_request_per_trhead;
};