#include "../../scenario_templates/many_objects/executeTestFunction.h"
#include "../helpers/olink_network_protocol_handler_for_test.hpp"
#include "../helpers/inspected_sink.h"
#include "../helpers/prepare_test_data.h"

#include <memory>


struct PropertyIntTestData
{
public:
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return sink->propertyChangedTimes == sentRequestsNumber;
    }
    std::shared_ptr<InspectedSink> sink;
    std::function<void(int)> testFunction;
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


    StringPropertySetter setter(messages_number);
    auto testData = getTestData<PropertyIntTestData, StringPropertySetter>(setter);

    auto portNumber = 8000;
    auto hostAddress = "127.0.0.1";
    OLinkHandlerForTest olinkProtocolHandler(hostAddress, portNumber);

    auto clientThread = executeTestFunction(testData, olinkProtocolHandler, messages_number);

    return app.exec();
}
