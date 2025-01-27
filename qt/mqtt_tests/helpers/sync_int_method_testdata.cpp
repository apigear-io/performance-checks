#include "sync_int_method_testdata.h"

#include "../helpers/itestsink.h"

#include <memory>
#include <vector>
#include <chrono>
#include <QtConcurrent>


SyncIntMethodTestData::SyncIntMethodTestData(std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> sink, std::vector<uint32_t>& latencies)
    :m_sink(sink),
    m_latencies(latencies)
{
}

bool SyncIntMethodTestData::allResponsesReceived (uint32_t sentRequestsNumber) const
{
    return receivedMsgs == sentRequestsNumber;
}

bool SyncIntMethodTestData::isReady() const
{
    return m_sink->isReady();
}

void SyncIntMethodTestData::testFunction(uint32_t value)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto val = m_sink->funcInt(value);
    auto end = std::chrono::high_resolution_clock::now();

    m_latencies[val] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    receivedMsgs++;
}
