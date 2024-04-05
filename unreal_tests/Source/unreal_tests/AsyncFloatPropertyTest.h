#pragma once


#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "Generated/api/AbstractApiTestApi0.h"
#include "AbstractTestBase.h"

#include "Counter.h"

#include <memory>
#include <vector>
#include <chrono>

#include "AsyncFloatPropertyTest.generated.h"


UCLASS()
class UAsyncFloatPropertyTest : public UAbstractTestBase
{
    GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0, int requestsPerCall, int callsNumber)
    {
        m_clientApi0 = clientApi0;
        m_request_per_trhead = requestsPerCall;
        int messages_number = requestsPerCall * callsNumber;
    }
    void start(int startNumber)
    {
        for (auto i = 0; i < m_request_per_trhead; i++)
        {
            auto number = startNumber + i;
            m_clientApi0->Execute_SetPropFloat(m_clientApi0, number + 1.0f + number / 1000.0f);
        }
    }

private:
    UApiTestApi0OLinkClient* m_clientApi0;
    int m_request_per_trhead;
};

