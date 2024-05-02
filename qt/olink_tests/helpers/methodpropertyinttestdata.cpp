#include "methodpropertyinttestdata.h"

#include "../helpers/test_sink.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"

#include <memory>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <QtConcurrent>


MethodPropertyIntTestData::MethodPropertyIntTestData(std::vector<uint32_t>& latencies)
    :m_latencies(latencies)
{
    sink = std::make_shared<TestSink>();
}

bool MethodPropertyIntTestData::allResponsesReceived (uint32_t sentRequestsNumber) const
{
    return receivedMsgs == sentRequestsNumber;
}

void MethodPropertyIntTestData::testFunctionBase(uint32_t value)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto val = sink->funcInt(value);
    auto end = std::chrono::high_resolution_clock::now();

    m_latencies[val] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    receivedMsgs++;
}

SyncMethodPropertyIntTestData::SyncMethodPropertyIntTestData(std::vector<uint32_t>& latencies)
    :MethodPropertyIntTestData(latencies)
{
}

void SyncMethodPropertyIntTestData::testFunction(uint32_t value)
{
    testFunctionBase(value);
    while (receivedMsgs < value ){}
}

AsyncMethodPropertyIntTestData::AsyncMethodPropertyIntTestData(std::vector<uint32_t>& latencies)
    :MethodPropertyIntTestData(latencies)
{
    m_futures = std::vector<QFuture<void>>(latencies.size(), QFuture<void>());
}


void AsyncMethodPropertyIntTestData::testFunction(uint32_t value)
{
    m_futures[value] = QtConcurrent::run([value, this](){testFunctionBase(value);});
}
