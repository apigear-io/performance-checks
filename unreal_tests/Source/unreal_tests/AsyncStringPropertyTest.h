#pragma once

#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "Generated/api/AbstractApiTestApi0.h"
#include "AbstractTestBase.h"
#include "Counter.h"

#include <memory>
#include <vector>
#include <chrono>

#include "AsyncStringPropertyTest.generated.h"

UCLASS()
class UAsyncStringPropertyTest : public UAbstractTestBase
{
    GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0, int requestsPerCall, int callsNumber)
    {
        m_clientApi0 = clientApi0;
        m_request_per_trhead = requestsPerCall;
        int messages_number = requestsPerCall * callsNumber;
        prepareStringMessages(messagesToSend, messages_number);
    }
    void start(int startNumber)
    {
        for (auto i = 0; i < m_request_per_trhead; i++)
        {
            auto number = startNumber + i;
            m_clientApi0->Execute_SetPropString(m_clientApi0, messagesToSend[number]);
        }
    }

private:
    void prepareStringMessages(std::vector<FString>& in_messagesToSend, int messages_number)
    {
        for (int msgNo = 0u; msgNo < messages_number; msgNo++)
        {
            auto message = FString(std::string("Some longer property to be set, prepared before test for each message number to reduce allocating time in tests" + std::to_string(msgNo)).c_str());
            in_messagesToSend.push_back(message);
        }
    }
    UApiTestApi0OLinkClient* m_clientApi0;
    int m_request_per_trhead;
    std::vector<FString> messagesToSend;
};