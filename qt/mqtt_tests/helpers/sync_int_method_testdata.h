#ifndef MQTT_SYNC_INT_METHOD_DATA_H
#define MQTT_SYNC_INT_METHOD_DATA_H


#include "itestsink.h"
#include "api/mqtt/mqtttestapi0.h"
#include <memory>
#include <vector>
#include <chrono>
#include <QFuture>

class SyncIntMethodTestData : public QObject
{
    Q_OBJECT
public:
    SyncIntMethodTestData(std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> sink, std::vector<uint32_t>& latencies);
    bool allResponsesReceived (uint32_t sentRequestsNumber) const;

    virtual void testFunction(uint32_t value);
    bool isReady() const;
private:
    std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> m_sink;
    std::atomic<uint32_t> receivedMsgs{0u};
    std::vector<uint32_t>& m_latencies;
};

#endif // MQTT_SYNC_INT_METHOD_DATA_H
