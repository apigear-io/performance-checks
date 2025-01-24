#pragma once

#include "apigear/nats/natsclient.h"
#include "test_message_topics.h"
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <iostream>
#include <chrono>


class NatsHandlerForTest
{
public:
    NatsHandlerForTest(std::string brokerUrl)
        :m_brokerUrl(brokerUrl)
    {
        m_client = std::make_shared<ApiGear::Nats::Client>();
    }

    void prepareConnection()
    {
        m_client->connect(m_brokerUrl);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    template<class TestData>
    void connectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            int number = 0;
            auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
            m_client->publish(NatsTestMessages::clientStartsTestTopic, { payload });
        }
    }

    template<class TestData>
    void connectObjects(TestData& testData)
    {
        static int number = 0;
        auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
        m_client->publish(NatsTestMessages::clientStartsTestTopic,{ payload });
    }

    template<class TestData>
    void disconnectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            int number = 0;
            auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
            m_client->publish(NatsTestMessages::clientStopsTestTopic, { payload });
        }
    }
    template<class TestData>
    void disconnectObjects(TestData& testData)
    {
        static int number = 0;
        auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
        m_client->publish(NatsTestMessages::clientStopsTestTopic, { payload });
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
                if (element.receivedMessages() == messages_number)
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
            allMessagesReceived = testData.receivedMessages() == messages_number;
        }
        std::cout << "finishing " << testData.receivedMessages() << std::endl;
    }

    template<class TestData>
    void waitUntilObjectConnected(const TestData& object)
    {
        while (!object.isReady())
        {
            // wait until ready to use.
        }
    }
    std::shared_ptr<ApiGear::Nats::Client> getClient()
    {
        return m_client;
    }
private:
    std::string m_brokerUrl;
    std::shared_ptr<ApiGear::Nats::Client> m_client;
};
