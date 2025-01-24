#include "sync_int_method_testdata.h"

#include "../helpers/test_sink.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"

#include <memory>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <QtConcurrent>


SyncIntMethodTestData::SyncIntMethodTestData(std::vector<uint32_t>& latencies)
    :m_latencies(latencies)
{
    sink = std::make_shared<TestSink>();
}

bool SyncIntMethodTestData::allResponsesReceived (uint32_t sentRequestsNumber) const
{
    return receivedMsgs == sentRequestsNumber;
}

void SyncIntMethodTestData::testFunction(uint32_t value)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto val = sink->funcInt(value);
    auto end = std::chrono::high_resolution_clock::now();

    m_latencies[val] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    receivedMsgs++;
}
