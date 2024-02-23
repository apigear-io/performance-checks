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


MethodPropertyIntTestData::MethodPropertyIntTestData(std::vector<uint32_t>& latencies)
    :m_latencies(latencies)
{
    sink = std::make_shared<TestSink>();
    connect(this, &SyncMethodPropertyIntTestData::executeFunctionSignal, this, &SyncMethodPropertyIntTestData::testFunctionSlot);
}

bool MethodPropertyIntTestData::allResponsesReceived (uint32_t sentRequestsNumber) const
{
    return receivedMsgs == sentRequestsNumber;
}

void MethodPropertyIntTestData::testFunctionSlot(uint32_t value)
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
    emit executeFunctionSignal(value);
    while (receivedMsgs < value ){}
}

AsyncMethodPropertyIntTestData::AsyncMethodPropertyIntTestData(std::vector<uint32_t>& latencies)
    :MethodPropertyIntTestData(latencies)
{
}


void AsyncMethodPropertyIntTestData::testFunction(uint32_t value)
{
    emit executeFunctionSignal(value);
}
