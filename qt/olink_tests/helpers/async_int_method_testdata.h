#ifndef OLINK_ASYNC_INT_METHOD_DATA_H
#define OLINK_ASYNC_INT_METHOD_DATA_H


#include "test_sink.h"
#include "../latency_helper/latency_helper.h"

#include <memory>
#include <vector>
#include <QFuture>

class AsyncIntMethodTestData : public QObject
{
    Q_OBJECT
public:
    AsyncIntMethodTestData(std::vector<chrono_hr_timepoint>& timestampStart, std::vector<chrono_hr_timepoint>& timestampStop);
    bool allResponsesReceived (uint32_t sentRequestsNumber) const;
    std::shared_ptr<TestSink> sink;

    virtual void testFunction(uint32_t value);
private:
    std::atomic<uint32_t> receivedMsgs{0u};
    std::vector<chrono_hr_timepoint>& m_timestampStart;
    std::vector<chrono_hr_timepoint>& m_timestampStop;
    std::vector<QFuture<int>> m_futures;
};

#endif // OLINK_ASYNC_INT_METHOD_DATA_H
