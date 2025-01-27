#include "../helpers/itestsink.h"
#include "api/mqtt/mqtttestapi0.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include <QtCore>

#include <memory>


class PropertyIntTestData
{
public:
    PropertyIntTestData(ApiGear::Mqtt::Client& client, std::vector<uint32_t>& latencies)
        : m_latencies(latencies)
    {
        sink =  std::make_shared<TestSink<api::MqttTestApi0,api::AbstractTestApi0>>(client);
    }

    void testFunction(uint32_t value)
    {
        auto start = std::chrono::high_resolution_clock::now();
        // Add one, to avoid setting property to 0 as first call, 0 is default property and it won't be set for same value.
        sink->setPropInt(value + 1);
        // wait for response for this one.
        while (!sink->allResponsesReceived(value +1))
        {
        }
        auto end = std::chrono::high_resolution_clock::now();
        m_latencies[value] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    }

    bool isReady() const
    {
        return sink->isReady();
    }

    const QString objectName() const
    {
        return sink->objectName();
    }

    bool allResponsesReceived(uint32_t messages_number) const
    {
        return sink->allResponsesReceived(messages_number);
    }

private:
    std::vector<uint32_t>& m_latencies;
    std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> sink;
};

/*
By default test request property int change 1000 times from each of 100 threads.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    auto sendThreadNumber = 100u;
    auto messages_number = 500u;
    auto total_messages_number = sendThreadNumber * messages_number;
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
    std::vector<uint32_t> m_latencies(total_messages_number, 0);
    MqttHandlerForTest networkProtocolHandler(address, portNumber);

    PropertyIntTestData testObject(networkProtocolHandler.getClient(), m_latencies);
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);

    return app.exec();
}

