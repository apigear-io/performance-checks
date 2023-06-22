#pragma once

#include "olink/clientnode.h"
#include "olink/clientregistry.h"
#include "apigear/olink/olinkconnection.h"
#include <vector>
#include <string>
#include <memory>


class OLinkHandlerForTest
{
public:
    void prepareConnection(std::string hostAddress, uint32_t portNumber)
    {
        auto full_address = "ws://" + hostAddress + ":" + std::to_string(portNumber);
        m_client = std::make_unique<ApiGear::PocoImpl::OlinkConnection>(registry);
        m_client->connectToHost(Poco::URI(full_address));
    }

    template<class TestData>
    void connectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            m_client->connectAndLinkObject(element.sink);
        }
    }

    template<class TestData>
    void disconnectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            m_client->disconnectAndUnlink(element.sink->olinkObjectName());
        }
    }

    template<class TestData>
    void waitForReturnMessages(const std::vector<TestData>& testData, uint32_t messages_number)
    {
        auto allMessagesReceived = false;
        while (!allMessagesReceived)
        {
            auto serviceWithAllMessages = 0u;
            for (const auto& element : testData)
            {
                if (element.sink->propertyChangedTimes == messages_number)
                {
                    serviceWithAllMessages++;
                }
            }
            allMessagesReceived = serviceWithAllMessages == testData.size();
        }
    }

    template<class TestData>
    void waitUntilObjectConnected(const TestData& object)
    {
        while (!object.sink->isReady ())
        {
            // wait until ready to use.
        }
    }
private:
    ApiGear::ObjectLink::ClientRegistry registry;
    std::unique_ptr<ApiGear::PocoImpl::OlinkConnection> m_client;
};