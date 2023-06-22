#pragma once

#include "olink/clientregistry.h"
#include "apigear/olink/olinkclient.h"
#include <vector>
#include <string>
#include <memory>


class OLinkHandlerForTest
{
public:

    void prepareConnection(std::string hostAddress, uint32_t portNumber)
    {
        auto full_address = "ws://" + hostAddress + ":" + std::to_string(portNumber) + "/ws";
        auto qstringAddr = QString::fromStdString(full_address);
        auto url = QUrl(qstringAddr);
        m_client = std::make_unique<ApiGear::ObjectLink::OLinkClient>(m_registry);
        m_client->connectToHost(url);
    }

    template<class TestData>
    void connectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            m_client->linkObjectSource(element.sink);
        }
    }

    template<class TestData>
    void disconnectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            m_client->unlinkObjectSource(element.sink->olinkObjectName());
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
        while (!object.sink->isReady())
        {
            // wait until ready to use.
        }
    }
private:
    ApiGear::ObjectLink::ClientRegistry m_registry;
    std::unique_ptr<ApiGear::ObjectLink::OLinkClient> m_client;
};
