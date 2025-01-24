#pragma once

#include "apigear/mqtt/mqttclient.h"
#include "test_message_topics.h"
#include <vector>
#include <string>
#include <memory>
#include <condition_variable>


class MqttHandlerForTest
{
public:
    MqttHandlerForTest(QString hostAddress, uint32_t portNumber)
        :host(hostAddress),
        port(portNumber)
    {
        m_client = std::make_unique<ApiGear::Mqtt::Client>("VeryUniqueClientId");
        m_client->connect(m_client.get(), &ApiGear::Mqtt::Client::ready, [this](){ isConnectedFlag = true;});
    }

    void prepareConnection()
    {
        m_client->connectToHost(host,port);
    }

    template<class TestData>
    void connectObjects(std::vector<TestData>& testData)
    {
        std::unique_lock<std::mutex> lock(m_isConnectedMutex);
        m_isConnected.wait_for(lock, std::chrono::milliseconds(500), [this]() {return isConnectedFlag == true; });
        lock.unlock();
        for (auto& element : testData)
        {
            QString name = element.objectName();
            m_client->setRemoteProperty(TestMessages::clientStartsTestTopic, {name.toStdString()});
        }
    }

    template<class TestData>
    void connectObjects(TestData& testData)
    {
        std::unique_lock<std::mutex> lock(m_isConnectedMutex);
        m_isConnected.wait_for(lock, std::chrono::milliseconds(5000), [this]() {return isConnectedFlag == true; });
        lock.unlock();
        QString name = testData.objectName();
        m_client->setRemoteProperty(TestMessages::clientStartsTestTopic,{name.toStdString()});
    }

    template<class TestData>
    void disconnectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            QString name = element.objectName();
            m_client->setRemoteProperty(TestMessages::clientStopsTestTopic, {name.toStdString()});
        }
    }
    template<class TestData>
    void disconnectObjects(TestData& testData)
    {
        qDebug()<<"sending STOP ";
        QString name = testData.objectName();
        m_client->setRemoteProperty(TestMessages::clientStopsTestTopic, {name.toStdString()});
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
                if (element.allResponsesReceived(messages_number))
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
        while (!object.isReady())
        {
            // wait until ready to use.
        }
    }
    ApiGear::Mqtt::Client& getClient()
    {
        return *(m_client.get());
    }
private:
    QString host;
    uint32_t port;
    std::unique_ptr<ApiGear::Mqtt::Client> m_client;
    std::condition_variable m_isConnected;
    std::atomic<bool> isConnectedFlag{false};
    std::mutex m_isConnectedMutex;
};
