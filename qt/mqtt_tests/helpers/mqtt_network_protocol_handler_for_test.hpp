#pragma once

#include "apigear/mqtt/mqttclient.h"
#include "test_message_topics.h"
#include <vector>
#include <string>
#include <memory>


class MqttHandlerForTest
{
public:
    MqttHandlerForTest(QString hostAddress, uint32_t portNumber)
        :host(hostAddress),
        port(portNumber)
    {
        m_client = std::make_unique<ApiGear::Mqtt::Client>("VeryUniqueClientId");
    }

    void prepareConnection()
    {
        m_client->connectToHost(host,port);
    }

    template<class TestData>
    void connectObjects(std::vector<TestData>& testData)
    {
        while (!m_client->isReady())
        {
            // wait until ready to use.
        }
        for (auto& element : testData)
        {
            QString name = element.sink->objectName();
            m_client->setRemoteProperty(TestMessages::clientStartsTestTopic, {name.toStdString()});
        }
    }

    template<class TestData>
    void connectObjects(TestData& testData)
    {

        while (!m_client->isReady())
        {
            // wait until ready to use.
        }
        QString name = testData.sink->objectName();
        m_client->setRemoteProperty(TestMessages::clientStartsTestTopic,{name.toStdString()});
    }

    template<class TestData>
    void disconnectObjects(std::vector<TestData>& testData)
    {
        for (auto& element : testData)
        {
            QString name = element.sink->objectName();
            m_client->setRemoteProperty(TestMessages::clientStopsTestTopic, {name.toStdString()});
        }
    }
    template<class TestData>
    void disconnectObjects(TestData& testData)
    {
        qDebug()<<"sending STOP ";
        QString name = testData.sink->objectName();
        m_client->setRemoteProperty(TestMessages::clientStopsTestTopic, {name.toStdString()});
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
    void waitForReturnMessages(TestData& testData, uint32_t messages_number)
    {
        auto allMessagesReceived = false;
        while (!allMessagesReceived)
        {
            allMessagesReceived = testData.sink->propertyChangedTimes == messages_number;
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
    ApiGear::Mqtt::Client& getClient()
    {
        return *(m_client.get());
    }
private:
    QString host;
    uint32_t port;
    std::unique_ptr<ApiGear::Mqtt::Client> m_client;
};
