#pragma once

#include "apigear/mqtt/mqttclient.h"
#include "test_message_topics.h"
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <chrono>


class MqttHandlerForTest
{
public:
    MqttHandlerForTest(std::string brokerUrl)
        :m_brokerUrl(brokerUrl)
    {
        m_client = std::make_shared<ApiGear::MQTT::Client>("VeryUniqueClientId");
    }

    void prepareConnection()
    {
        m_client->connectToHost(m_brokerUrl);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    template<class TestData>
    void connectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            int number = 0;
            auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
            m_client->setRemoteProperty(TestMessages::clientStartsTestTopic, { payload });
        }
    }

    template<class TestData>
    void connectObjects(TestData& testData)
    {
        static int number = 0;
        auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
        m_client->setRemoteProperty(TestMessages::clientStartsTestTopic,{ payload });
    }

    template<class TestData>
    void disconnectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            int number = 0;
            auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
            m_client->setRemoteProperty(TestMessages::clientStopsTestTopic, { payload });
        }
    }
    template<class TestData>
    void disconnectObjects(TestData& testData)
    {
        static int number = 0;
        auto payload = (nlohmann::json({ "object no " + std::to_string(number++) }).dump());
        m_client->setRemoteProperty(TestMessages::clientStopsTestTopic, { payload });
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
                if (element.sink->receivedMessages() == messages_number)
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
            allMessagesReceived = testData.sink->receivedMessages() == messages_number;
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
    std::shared_ptr<ApiGear::MQTT::Client> getClient()
    {
        return m_client;
    }
private:
    std::string m_brokerUrl;
    std::shared_ptr<ApiGear::MQTT::Client> m_client;
};
