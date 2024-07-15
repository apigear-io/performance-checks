#ifndef SYNCMETHODPROPERTYINTTESTDATA_H
#define SYNCMETHODPROPERTYINTTESTDATA_H

#include "api/mqtt/mqtttestapi0.h"

#include <memory>
#include <vector>
#include <QFuture>


class MethodIntTestData : public QObject
{
    Q_OBJECT
public:
    MethodIntTestData(ApiGear::Mqtt::Client& client, std::vector<uint32_t>& latencies);

    virtual void testFunction(uint32_t value) = 0;

    void testFunctionBase(uint32_t value);

    bool isReady() const
    {
        return m_ready;
    }

    const QString objectName()
    {
        return sink->objectName();
    }

    bool allResponsesReceived(uint32_t messages_number)
    {
        return receivedMsgs == messages_number;
    }

protected:
    std::atomic<uint32_t> receivedMsgs{0u};
private:
    bool allResponsesReceived (uint32_t sentRequestsNumber) const;
    std::shared_ptr<api::MqttTestApi0> sink;
    bool m_ready=false;
    std::vector<uint32_t>& m_latencies;
};
\
class SyncMethodIntTestData :public MethodIntTestData
{
public:
    SyncMethodIntTestData(ApiGear::Mqtt::Client& client, std::vector<uint32_t>& latencies);
    void testFunction(uint32_t value) override;
};

class AsyncMethodIntTestData :public MethodIntTestData
{
public:
    AsyncMethodIntTestData(ApiGear::Mqtt::Client& client, std::vector<uint32_t>& latencies);
    void testFunction(uint32_t value) override;

    std::vector<QFuture<void>> m_futures;
};

#endif // SYNCMETHODPROPERTYINTTESTDATA_H
