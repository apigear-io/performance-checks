//#include "../helpers/test_sink.h"
#include "api/mqtt/mqtttestapi0.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include <QtCore>

#include <memory>


class TestSink : public api::MqttTestApi0
{
public:
    TestSink(ApiGear::Mqtt::Client& client)
        :api::MqttTestApi0(client)
    {
        connect(this, &AbstractTestApi0::propIntChanged, this, &TestSink::propertyChanged, Qt::QueuedConnection);//TEST SPECIFIC
        connect(&client, &ApiGear::Mqtt::Client::ready, [this](){ m_isReady = true;});// should be in ITestSink
    }

    bool isReady()//REQUIRED, should be in ITestSink
    {
        return m_isReady;
    }

    void propertyChanged(int value)
    {
        propertyChangedTimes++;
    }

    uint32_t propertyChangedTimes = 0;//REQUIRED, should be in ITestSink
    bool m_isReady = false;
};


class PropertyIntTestData
{
public:
    PropertyIntTestData(ApiGear::Mqtt::Client& client)
    {
        sink = std::make_shared<TestSink>(client);
    }

    void testFunction(uint32_t value)
    {
        // Add one, to avoid setting property to 0 as first call, 0 is default property and it won't be set for same value.
        sink->setPropInt(value + 1);
    }
public:
    std::shared_ptr<TestSink> sink;
};

/*
By default test request property int change 1000 times from each of 100 threads.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    auto sendThreadNumber = 1u;
    auto messages_number = 3000u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }
    if (argc > 2)
    {
        char* p;
        sendThreadNumber = strtol(argv[2], &p, 10);
    }

    quint16 portNumber = 1883;
    QString address = "localhost";
    MqttHandlerForTest networkProtocolHandler(address, portNumber);

    PropertyIntTestData testObject(networkProtocolHandler.getClient());
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);

    return app.exec();
}

