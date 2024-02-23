#pragma once

#include "olink/clientregistry.h"
#include "apigear/olink/olinkclient.h"
#include <vector>
#include <string>
#include <memory>


class OLinkHandlerForTest
{
public:
    OLinkHandlerForTest(QString hostAddress, uint32_t portNumber)
        :host(hostAddress),
        port(portNumber)
    {
    }

    void prepareConnection()
    {
        auto full_address = "ws://" + host.toStdString() + ":" + std::to_string(port) + "/ws";
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
    void connectObjects(TestData& testData)
    {
        m_client->linkObjectSource(testData.sink);
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
    void disconnectObjects(TestData& testData)
    {
        m_client->unlinkObjectSource(testData.sink->olinkObjectName());
    }

    template<class TestData>
    void waitForReturnMessages(std::vector<TestData>& testData, uint32_t messages_number)
    {
        auto allMessagesReceived = false;
        while (!allMessagesReceived)
        {
            auto serviceWithAllMessages = 0u;
            for (const auto& element : testData)
            {
                if (element.sink->allResponsesReceived(messages_number))
                {
                    serviceWithAllMessages++;
                }
            }
            allMessagesReceived = serviceWithAllMessages == testData.size();
        }
    }

    template<class TestData>
    void waitForReturnMessages(TestData& testData, uint32_t messages_number)
    {
        auto allMessagesReceived = false;
        while (!allMessagesReceived)
        {
            allMessagesReceived = testData.allResponsesReceived(messages_number);
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
    QString host;
    uint32_t port;
    ApiGear::ObjectLink::ClientRegistry m_registry;
    std::unique_ptr<ApiGear::ObjectLink::OLinkClient> m_client;
};
