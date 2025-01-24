#include "async_int_method_testdata.h"

#include "../helpers/test_sink.h"

#include <memory>
#include <vector>
#include <chrono>
#include <QtConcurrent>


AsyncIntMethodTestData::AsyncIntMethodTestData(std::vector<chrono_hr_timepoint>& timestampStart, std::vector<chrono_hr_timepoint>& timestampStop)
    :m_timestampStart(timestampStart),
     m_timestampStop(timestampStop),
    m_futures(std::vector<QFuture<int>>(m_timestampStop.size(),QFuture<int>()))
{
    sink = std::make_shared<TestSink>();

}

bool AsyncIntMethodTestData::allResponsesReceived (uint32_t sentRequestsNumber) const
{
    return receivedMsgs == sentRequestsNumber;
}

void AsyncIntMethodTestData::testFunction(uint32_t value)
{
    m_timestampStart[value] = std::chrono::high_resolution_clock::now();
    auto future = sink->funcIntAsync(value);
    future.then([this](uint32_t value)
                {
                    m_timestampStop[value] = std::chrono::high_resolution_clock::now();
                    receivedMsgs++;;
    });
    m_futures[value] = future;

}
