#include "api/mqtt/mqtttestapi0.h"
#include "../helpers/itestsink.h"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include <memory>

struct PropertyStringTestData
{
public:

    PropertyStringTestData(ApiGear::Mqtt::Client& client, uint32_t messages_number, uint32_t sendThreadNumber)
    {
        for (int msgNo = 0u; msgNo < sendThreadNumber*(messages_number +1); msgNo++)
        {
            auto message = "Some longer property to be set, prepared before test for each message number to reduce allocating time in tests"+ std::to_string(msgNo);
            messagesToSend.push_back(QString::fromStdString(message));
        }

        auto obj =  std::make_shared<TestSink<api::MqttTestApi0,api::AbstractTestApi0>>(client);
        m_testFunction = [obj, this](uint32_t value)
        {
            obj->setPropString(messagesToSend[value]);
        };
        sink = obj;
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

    void testFunction(uint32_t value)
    {
        m_testFunction(value);
    }
private:
    std::shared_ptr<ITestSink> sink;
    std::function<void(uint32_t)> m_testFunction;
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
    auto sendThreadNumber = 10u;
    auto messages_number = 100u;
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

    PropertyStringTestData testObject(networkProtocolHandler.getClient(), messages_number,sendThreadNumber);
    auto clientThread = executeTestFunction(testObject, networkProtocolHandler, messages_number, sendThreadNumber);


    return app.exec();
}

