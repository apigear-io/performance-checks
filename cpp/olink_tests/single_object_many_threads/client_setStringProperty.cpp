#include "test_sink.h"

#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

#include <memory>
#include <string>

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
            messagesToSend.push_back("Some longer property to be set, prepared before test for each message number to reduce allocating time in tests"
                    + std::to_string(msgNo));//make every message different
        }

    }
private:
    // Prepare messages to send before test starts not to slow down it with allocation of this many messages:
    std::vector<std::string> messagesToSend;
};

/*
By default test request property string change 1000 times from each of 100 threads.
Each message is over 100 character long.
Test waits for the responses after sending all the messages, not for each one.
You can play around with running this program with different messages number and different threads number.
*/
int main(int argc, char* argv[])
{
    std::vector<uint16_t> timePerMessage;
    auto sendThreadNumber = 100u;
    auto messages_number = 1000;
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
    OLinkHandlerForTest olinkProtocolHandler(hostAddress, portNumber);
    auto testObject = PropertyStringTestData(sendThreadNumber, messages_number);

    executeTestFunction(testObject, olinkProtocolHandler, messages_number, sendThreadNumber);

}