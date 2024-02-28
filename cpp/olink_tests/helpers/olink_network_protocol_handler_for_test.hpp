#pragma once

#include "olink/clientnode.h"
#include "olink/clientregistry.h"
#include "apigear/olink/olinkconnection.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>


class OLinkHandlerForTest
{
public:
    OLinkHandlerForTest(std::string hostAddress, uint32_t portNumber)
        :m_hostAddress(hostAddress),
        m_portNumber(portNumber)
    {}

    void prepareConnection()
    {
        auto full_address = "ws://" + m_hostAddress + ":" + std::to_string(m_portNumber) + "/ws";
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
    void connectObjects(TestData& testData)
    {
        m_client->connectAndLinkObject(testData.sink);
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
    void disconnectObjects(TestData& testData)
    {
        m_client->disconnectAndUnlink(testData.sink->olinkObjectName());
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
                if (element.allResponsesReceived(messages_number))
                {
                    serviceWithAllMessages++;
                }
            }
            allMessagesReceived = serviceWithAllMessages == testData.size();
        }
    }


    template<class TestData>
    void waitForReturnMessages(const TestData& testData, uint32_t messages_number)
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
    std::string m_hostAddress;
    uint32_t m_portNumber;
    ApiGear::ObjectLink::ClientRegistry registry;
    std::unique_ptr<ApiGear::PocoImpl::OlinkConnection> m_client;
};