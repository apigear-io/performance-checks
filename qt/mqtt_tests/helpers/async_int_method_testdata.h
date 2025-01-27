#ifndef MQTT_ASYNC_INT_METHOD_DATA_H
#define MQTT_ASYNC_INT_METHOD_DATA_H


#include "itestsink.h"
#include "../../latency_helper/latency_helper.h"
#include "api/mqtt/mqtttestapi0.h"

#include <memory>
#include <vector>
#include <QFuture>

class AsyncIntMethodTestData : public QObject
{
    Q_OBJECT
public:
    AsyncIntMethodTestData(std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> sink,
                           std::vector<chrono_hr_timepoint>& timestampStart,
                           std::vector<chrono_hr_timepoint>& timestampStop);
    bool allResponsesReceived (uint32_t sentRequestsNumber) const;

    virtual void testFunction(uint32_t value);
    bool isReady() const;

private:
    std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> m_sink;
    std::atomic<uint32_t> receivedMsgs{0u};
    std::vector<chrono_hr_timepoint>& m_timestampStart;
    std::vector<chrono_hr_timepoint>& m_timestampStop;
    std::vector<QFuture<int>> m_futures;
};

#endif // MQTT_ASYNC_INT_METHOD_DATA_H
