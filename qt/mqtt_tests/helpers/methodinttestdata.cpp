#include "methodinttestdata.h"

#include <memory>
#include <vector>
#include <chrono>
#include <QtConcurrent>


MethodIntTestData::MethodIntTestData(ApiGear::Mqtt::Client& client, std::vector<uint32_t>& latencies)
    : m_latencies(latencies)
{
    sink =  std::make_shared<api::MqttTestApi0>(client);
    api::MqttTestApi0::connect(&client, &ApiGear::Mqtt::Client::ready, [this](){ m_ready = true;});
}

bool MethodIntTestData::allResponsesReceived (uint32_t sentRequestsNumber) const
{
    return receivedMsgs == sentRequestsNumber;
}

void MethodIntTestData::testFunctionBase(uint32_t value)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto val = sink->funcInt(value);
    auto end = std::chrono::high_resolution_clock::now();

    m_latencies[value] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    receivedMsgs++;
}

SyncMethodIntTestData::SyncMethodIntTestData(ApiGear::Mqtt::Client& client, std::vector<uint32_t>& latencies)
    :MethodIntTestData(client, latencies)
{
}

void SyncMethodIntTestData::testFunction(uint32_t value)
{
    testFunctionBase(value);
    while (receivedMsgs < value ){}
}

AsyncMethodIntTestData::AsyncMethodIntTestData(ApiGear::Mqtt::Client& client, std::vector<uint32_t>& latencies)
    :MethodIntTestData(client, latencies)
{
    m_futures = std::vector<QFuture<void>>(latencies.size(), QFuture<void>());
}


void AsyncMethodIntTestData::testFunction(uint32_t value)
{
    m_futures[value] = QtConcurrent::run([value, this](){testFunctionBase(value);});
}
