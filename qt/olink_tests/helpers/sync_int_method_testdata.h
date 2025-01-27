#ifndef OLINK_SYNC_INT_METHOD_DATA_H
#define OLINK_SYNC_INT_METHOD_DATA_H


#include "test_sink.h"

#include <memory>
#include <vector>
#include <chrono>
#include <algorithm>
#include <QFuture>

class SyncIntMethodTestData : public QObject
{
    Q_OBJECT
public:
    SyncIntMethodTestData(std::vector<uint32_t>& latencies);
    bool allResponsesReceived (uint32_t sentRequestsNumber) const;
    std::shared_ptr<TestSink> sink;

    virtual void testFunction(uint32_t value);
private:
    std::atomic<uint32_t> receivedMsgs{0u};
    std::vector<uint32_t>& m_latencies;
};

#endif // OLINK_SYNC_INT_METHOD_DATA_H
