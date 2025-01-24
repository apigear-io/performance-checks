#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/async_int_method_testdata.h"
#include "../../latency_helper/latency_helper.h"

#include <vector>
/*
By default test request property int change 10 times from each of 1 thread.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 1u;
    auto messages_number = 10u;
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

    auto portNumber = 8000;
    auto hostAddress = "127.0.0.1";
    OLinkHandlerForTest networkProtocolHandler(hostAddress, portNumber);

    std::vector<chrono_hr_timepoint> m_timeStart(total_messages_number, chrono_hr_timepoint());
    std::vector<chrono_hr_timepoint> m_timeStop(total_messages_number, chrono_hr_timepoint());
    auto testObject = AsyncIntMethodTestData(m_timeStart, m_timeStop);

    auto calculateLatencies = [&m_timeStart, &m_timeStop]()
    {
        calculateAndPrintLatencyParameters(m_timeStart, m_timeStop);
    };
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber, calculateLatencies);

    return app.exec();
}
