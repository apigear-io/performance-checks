#ifndef SYNCMETHODPROPERTYINTTESTDATA_H
#define SYNCMETHODPROPERTYINTTESTDATA_H


#include "test_sink.h"

#include <memory>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>

class MethodPropertyIntTestData : public QObject
{
    Q_OBJECT
public:
    MethodPropertyIntTestData(std::vector<uint32_t>& latencies);
    bool allResponsesReceived (uint32_t sentRequestsNumber) const;
    std::shared_ptr<TestSink> sink;

    virtual void testFunction(uint32_t value) = 0;
signals:
    void executeFunctionSignal(uint32_t value);

public slots:
    void testFunctionSlot(uint32_t value);

protected:
    std::atomic<uint32_t> receivedMsgs{0u};
private:
    std::vector<uint32_t>& m_latencies;
};
\
class SyncMethodPropertyIntTestData :public MethodPropertyIntTestData
{
public:
    SyncMethodPropertyIntTestData(std::vector<uint32_t>& latencies);
    void testFunction(uint32_t value) override;
};

class AsyncMethodPropertyIntTestData :public MethodPropertyIntTestData
{
public:
    AsyncMethodPropertyIntTestData(std::vector<uint32_t>& latencies);
    void testFunction(uint32_t value) override;
};

#endif // SYNCMETHODPROPERTYINTTESTDATA_H
