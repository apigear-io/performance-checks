#include "api/generated/nats/testapi0service.h"
#include "api/implementation/testapi0.h"
#include "apigear/nats/natsservice.h"
#include "../test_message_topics.h"
#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <thread>

/*
* Helper object that subscribes for test messages from remote clients.
* Client side test is supposed to send those on test start and finish.
*/
class TestWatcher
{
public:
    bool isStarted()
    {
        return countStartMessages > 0;
    }
    bool isFinished(){
        return  isStarted() && false;// countStartMessages == countStopMessages;
    }

    TestWatcher(ApiGear::Nats::Service& service)
        :m_service(service)
    {

       // m_service.subscribe(NatsTestMessages::clientStartsTestTopic, [this](const auto&) { countStartMessages++;  std::cout << "started"; }, [this](auto id, const auto& topic, bool succeed) {
       //     startTopicId = id; });
       //  m_service.subscribe(NatsTestMessages::clientStopsTestTopic, [this](const auto&) {countStopMessages++; std::cout << "stopped"; }, [this](auto id, const auto& topic, bool succeed) {
       //      stopTopicId = id; });
    }

    ~TestWatcher()
    {
       // m_service.unsubscribe(startTopicId);
       // m_service.unsubscribe(stopTopicId);
    }

private:
    int countStartMessages = 0;
    int countStopMessages = 0;
    uint32_t startTopicId = 0;
    uint32_t stopTopicId = 0;
    ApiGear::Nats::Service& m_service;
};

int main(int argc, char* argv[])
{
    auto service = std::make_shared<ApiGear::Nats::Service>();
    auto source = std::make_shared<Cpp::Api::TestApi0>();
    auto sourceService = Cpp::Api::Nats::TestApi0Service::create(source, service);
    TestWatcher testWatcher(*(service.get()));

    std::string brokerUrl = "nats://localhost:4222";
    service->connect(brokerUrl);


    bool testStarted = false;
    // Will be overwritten with receiving link message
    auto begin = std::chrono::high_resolution_clock::now();

    do {

        if (!testStarted && testWatcher.isStarted())
        {
            testStarted = true;
            begin = std::chrono::high_resolution_clock::now();
        }

    } while (!testWatcher.isFinished());
    auto end = std::chrono::high_resolution_clock::now();
    service->disconnect();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    auto test_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "server finished work, time measured [ms]" << test_duration.count() << std::endl;

}
