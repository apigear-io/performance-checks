#include "../../scenario_templates/many_objects/executeTestFunction.h"
#include "../helpers/mqtt_network_protocol_handler_for_test.hpp"
#include "../helpers/itestsink.h"
#include "../helpers/prepare_test_data.h"

#include <memory>


struct PropertyIntTestData
{
public:
    std::shared_ptr<ITestSink> sink;
    std::function<void(int)> testFunction;

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
};

class StringPropertySetter {
public:
    StringPropertySetter(int numberOfMessages)
    {
        for (int messageNo = 0u; messageNo < numberOfMessages; messageNo++)
        {
            messagesToSend.push_back(QString::fromStdString("Some longer property to be set, prepared before test for each message number to reduce allocating time in tests"
                    + std::to_string(messageNo)));
        }
    }

    template<class Interface>
    void testFunction(std::shared_ptr<Interface> object, int number)
    {
        object->setPropString(messagesToSend[number]);
    }

    // Prepare messages to send before test starts not to slow down it with allocation of this many messages:
    std::vector<QString> messagesToSend;
};

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    std::vector<uint16_t> timePerMessage;
    auto messages_number = 1000u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }


    quint16 portNumber = 1883;
    QString address = "localhost";
    MqttHandlerForTest networkProtocolHandler(address, portNumber);

    StringPropertySetter setter(messages_number);
    auto testData = getTestData<PropertyIntTestData, StringPropertySetter>(setter, networkProtocolHandler.getClient());

    auto clientThread = executeTestFunction(testData, networkProtocolHandler, messages_number);

    return app.exec();
}
