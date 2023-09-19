#include "apigear/mqtt/mqttservice.h"
#include "../helpers/test_message_topics.h"
#include "../helpers/prepare_test_services.h"
#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>


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

    TestWatcher(ApiGear::Mqtt::ServiceAdapter& service)
        :m_service(service)
    {
        m_service.connect(&m_service, &ApiGear::Mqtt::ServiceAdapter::ready, [this](){
            subscriptionIdStart = m_service.subscribeTopic(TestMessages::clientStartsTestTopic,
                                                           [this](const auto&){ countStartMessages++;  qDebug()<< "started "<< countStartMessages;});
            subscriptionIdStop = m_service.subscribeTopic(TestMessages::clientStopsTestTopic,
                                                          [this](const auto&){countStopMessages++; qDebug() << "stopped still "<< countStopMessages <<" connected";});
        });
    }

    ~TestWatcher()
    {
        m_service.unsubscribeTopic(subscriptionIdStart);
        m_service.unsubscribeTopic(subscriptionIdStop);
    }

private:
    quint64 subscriptionIdStart = 0;
    quint64 subscriptionIdStop = 0;
    int countStartMessages = 0;
    int countStopMessages = 0;
    ApiGear::Mqtt::ServiceAdapter& m_service;
};

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);


    ApiGear::Mqtt::ServiceAdapter service("SuperService1");
    TestWatcher testWatcher(service);
    prepareStaticServices(service);

    quint16 portNumber = 1883;
    QString address = "localhost";
    service.connectToHost(address, portNumber);

    auto serviceWorker = std::async(std::launch::async,
                                    [&testWatcher, &service](){
        bool alreadyStarted = false;
        // Will be overwritten with receiving link message

        auto begin = std::chrono::high_resolution_clock::now();
        do {

            if (!alreadyStarted && testWatcher.isStarted() )
            {
                alreadyStarted = true;
                begin = std::chrono::high_resolution_clock::now();
            }

        } while (!testWatcher.isFinished());
        auto end = std::chrono::high_resolution_clock::now();

        auto test_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << "server finished work, time measured " << test_duration.count() << std::endl;
    });

    return app.exec();
}
