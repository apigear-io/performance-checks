#include "async_int_method_testdata.h"

#include <memory>
#include <vector>
#include <chrono>
#include <QtConcurrent>


AsyncIntMethodTestData::AsyncIntMethodTestData(std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> sink,
                                               std::vector<chrono_hr_timepoint>& timestampStart,
                                               std::vector<chrono_hr_timepoint>& timestampStop)
    :m_sink(sink),
     m_timestampStart(timestampStart),
     m_timestampStop(timestampStop),
     m_futures(std::vector<QFuture<int>>(m_timestampStop.size(),QFuture<int>()))
{
}

bool AsyncIntMethodTestData::allResponsesReceived (uint32_t sentRequestsNumber) const
{
    return receivedMsgs == sentRequestsNumber;
}

bool AsyncIntMethodTestData::isReady() const
{
    return m_sink->isReady();
}


void AsyncIntMethodTestData::testFunction(uint32_t value)
{
    m_timestampStart[value] = std::chrono::high_resolution_clock::now();
    auto future = m_sink->funcIntAsync(value);
    future.then([this](uint32_t value)
                {
                    m_timestampStop[value] = std::chrono::high_resolution_clock::now();
                    receivedMsgs++;;
    });
    m_futures[value] = future;

}
