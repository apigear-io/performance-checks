#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include "../helpers/aync_int_property_testdata.h"
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
    MqttHandlerForTest networkProtocolHandler(address, portNumber);
    std::vector<chrono_hr_timepoint> m_timeStart(total_messages_number, chrono_hr_timepoint());
    std::vector<chrono_hr_timepoint> m_timeStop(total_messages_number, chrono_hr_timepoint());

    PropertyIntTestData testObject(networkProtocolHandler.getClient(), m_timeStart, m_timeStop);
    auto calculateLatencies = [&m_timeStart, &m_timeStop]()
    {
        calculateAndPrintLatencyParameters(m_timeStart, m_timeStop);
    };
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber, calculateLatencies);
    return app.exec();
}

