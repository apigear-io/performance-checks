#pragma once

#include <QtCore>
#include <apigear/mqtt/mqttclient.h>

class ITestSink
{
public:
    virtual bool isReady() const = 0;
    virtual const QString objectName() const= 0;
    virtual bool allResponsesReceived(uint32_t messages_number) const = 0;
};


template <class BaseMqttTestApi, class BaseAbstractTestApi>
class TestSink : public ITestSink, public BaseMqttTestApi
{
public:
    TestSink(ApiGear::Mqtt::Client& client)
        :BaseMqttTestApi(client)
    {
        BaseAbstractTestApi::connect(this, &BaseAbstractTestApi::propIntChanged, this, &TestSink::propertyChangedI, Qt::QueuedConnection);
        BaseAbstractTestApi::connect(this, &BaseAbstractTestApi::propFloatChanged, this, &TestSink::propertyChangedF, Qt::QueuedConnection);
        BaseAbstractTestApi::connect(this, &BaseAbstractTestApi::propStringChanged, this, &TestSink::propertyChangedS, Qt::QueuedConnection);
        BaseAbstractTestApi::connect(this, &BaseAbstractTestApi::sigInt, this, &TestSink::signalGotI, Qt::QueuedConnection);
        BaseAbstractTestApi::connect(this, &BaseAbstractTestApi::sigFloat, this, &TestSink::signalGotF, Qt::QueuedConnection);
        BaseAbstractTestApi::connect(this, &BaseAbstractTestApi::sigString, this, &TestSink::signalGotS, Qt::QueuedConnection);
        BaseAbstractTestApi::connect(&client, &ApiGear::Mqtt::Client::ready, [this](){ m_isReady = true;});
    }

    bool isReady() const override
    {
        return m_isReady;
    }

    const QString objectName() const override
    {
        static auto name = BaseAbstractTestApi::objectName();
        return name;
    }

    void propertyChangedI(int /*value*/)
    {
        msgReceived++;
    }
    void propertyChangedF(float /*value*/)
    {
        msgReceived++;
    }
    void propertyChangedS(const QString& /*value*/)
    {
        msgReceived++;
    }
    void signalGotI(int /*value*/)
    {
        msgReceived++;
    }
    void signalGotF(float /*value*/)
    {
        msgReceived++;
    }
    void signalGotS(const QString& /*value*/)
    {
        msgReceived++;
    }
    bool allResponsesReceived(uint32_t messages_number) const override
    {
        return msgReceived == messages_number;
    }
private:
    std::atomic<uint32_t> msgReceived { 0 };
    bool m_isReady = false;
};
