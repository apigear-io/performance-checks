#include "../helpers/test_sink.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include <memory>

struct PropertyStringTestData
{
public:
    std::shared_ptr<TestSink> sink;
    void testFunction(uint32_t number)
    {
        sink->setPropString(messagesToSend[number]);
    }

    PropertyStringTestData(uint32_t messages_number, uint32_t sendThreadNumber)
    {
        sink = std::make_shared<TestSink>();
        for (int msgNo = 0u; msgNo < sendThreadNumber*(messages_number +1); msgNo++)
        {
            auto message = "Some longer property to be set, prepared before test for each message number to reduce allocating time in tests"+ std::to_string(msgNo);
            messagesToSend.push_back(QString::fromStdString(message));
        }

    }
private:
    // Prepare different messages to send before test starts not to slow down it with allocation of this many messages:
    std::vector<QString> messagesToSend;
};

/*
By default test request property string change 600 times from each of 100 threads.
Each message is over 100 character long.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 100u;
    auto messages_number = 1000u;
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

    OLinkHandlerForTest networkProtocolHandler;

    auto testObject = PropertyStringTestData(messages_number,sendThreadNumber);
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);

    return app.exec();
}
