#include "api/generated/mqtt/testapi0service.h"
#include "api/implementation/testapi0.h"
#include "apigear/mqtt/mqttservice.h"
#include "../helpers/test_message_topics.h"
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
        return  isStarted() && countStartMessages == countStopMessages;
    }

    TestWatcher(ApiGear::MQTT::Service& service)
        :m_service(service)
    {

         m_service.subscribeTopic(TestMessages::clientStartsTestTopic, [this](const auto&, const auto&, const auto&){ countStartMessages++;  std::cout<< "started";});
         m_service.subscribeTopic(TestMessages::clientStopsTestTopic, [this](const auto&, const auto&, const auto&){countStopMessages++; std::cout << "stopped";});
    }

    ~TestWatcher()
    {
        m_service.unsubscribeTopic(TestMessages::clientStartsTestTopic);
        m_service.unsubscribeTopic(TestMessages::clientStopsTestTopic);
    }

private:
    int countStartMessages = 0;
    int countStopMessages = 0;
    ApiGear::MQTT::Service& m_service;
};

int main(int argc, char* argv[])
{
    auto service = std::make_shared<ApiGear::MQTT::Service>("SuperService1");
    auto source = std::make_shared<Cpp::Api::TestApi0>();
    auto sourceService = std::make_shared<Cpp::Api::MQTT::TestApi0Service>(source, service);
    TestWatcher testWatcher(*(service.get()));

    std::string brokerUrl = "tcp://localhost:1883";
    service->connectToHost(brokerUrl);


    bool testStarted = false;
    // Will be overwritten with receiving link message
    auto begin = std::chrono::high_resolution_clock::now();

    auto servicesfinished = false;
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
    std::cout << "server finished work, time measured " << test_duration.count() << std::endl;

}
