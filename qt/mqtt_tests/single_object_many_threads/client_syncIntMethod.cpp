#include "../helpers/sync_int_method_testdata.h"
#include "../../latency_helper/latency_helper.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include <QtCore>

#include <memory>


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
    auto total_messages_number = messages_number* sendThreadNumber;
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

    std::vector<uint32_t> m_latencies(total_messages_number, 0);
    auto mqttClientObject = std::make_shared<TestSink<api::MqttTestApi0,api::AbstractTestApi0>>(networkProtocolHandler.getClient());
    SyncIntMethodTestData testObject(mqttClientObject, m_latencies);
    auto calculateLatencies = [&m_latencies]()
    {
        calculateAndPrintLatencyParameters(m_latencies);
    };
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber, calculateLatencies);

    return app.exec();
}

