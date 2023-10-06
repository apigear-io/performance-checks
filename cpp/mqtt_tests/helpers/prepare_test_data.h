#include <iostream>
#include <vector>
#include <apigear/mqtt/mqttclient.h>
#include "itestsink.h"

#include "api/generated/mqtt/testapi0client.h"
#include "api/generated/mqtt/testapi1client.h"
#include "api/generated/mqtt/testapi2client.h"
#include "api/generated/mqtt/testapi3client.h"
#include "api/generated/mqtt/testapi4client.h"
#include "api/generated/mqtt/testapi5client.h"
#include "api/generated/mqtt/testapi6client.h"
#include "api/generated/mqtt/testapi7client.h"
#include "api/generated/mqtt/testapi8client.h"
#include "api/generated/mqtt/testapi9client.h"

#include "api/generated/mqtt/testapi10client.h"
#include "api/generated/mqtt/testapi11client.h"
#include "api/generated/mqtt/testapi12client.h"
#include "api/generated/mqtt/testapi13client.h"
#include "api/generated/mqtt/testapi14client.h"
#include "api/generated/mqtt/testapi15client.h"
#include "api/generated/mqtt/testapi16client.h"
#include "api/generated/mqtt/testapi17client.h"
#include "api/generated/mqtt/testapi18client.h"
#include "api/generated/mqtt/testapi19client.h"

#include "api/generated/mqtt/testapi20client.h"
#include "api/generated/mqtt/testapi21client.h"
#include "api/generated/mqtt/testapi22client.h"
#include "api/generated/mqtt/testapi23client.h"
#include "api/generated/mqtt/testapi24client.h"
#include "api/generated/mqtt/testapi25client.h"
#include "api/generated/mqtt/testapi26client.h"
#include "api/generated/mqtt/testapi27client.h"
#include "api/generated/mqtt/testapi28client.h"
#include "api/generated/mqtt/testapi29client.h"

#include "api/generated/mqtt/testapi30client.h"
#include "api/generated/mqtt/testapi31client.h"
#include "api/generated/mqtt/testapi32client.h"
#include "api/generated/mqtt/testapi33client.h"
#include "api/generated/mqtt/testapi34client.h"
#include "api/generated/mqtt/testapi35client.h"
#include "api/generated/mqtt/testapi36client.h"
#include "api/generated/mqtt/testapi37client.h"
#include "api/generated/mqtt/testapi38client.h"
#include "api/generated/mqtt/testapi39client.h"

#include "api/generated/mqtt/testapi40client.h"
#include "api/generated/mqtt/testapi41client.h"
#include "api/generated/mqtt/testapi42client.h"
#include "api/generated/mqtt/testapi43client.h"
#include "api/generated/mqtt/testapi44client.h"
#include "api/generated/mqtt/testapi45client.h"
#include "api/generated/mqtt/testapi46client.h"
#include "api/generated/mqtt/testapi47client.h"
#include "api/generated/mqtt/testapi48client.h"
#include "api/generated/mqtt/testapi49client.h"
//
//#include "api/generated/mqtt/testapi50client.h"
//#include "api/generated/mqtt/testapi51client.h"
//#include "api/generated/mqtt/testapi52client.h"
//#include "api/generated/mqtt/testapi53client.h"
//#include "api/generated/mqtt/testapi54client.h"
//#include "api/generated/mqtt/testapi55client.h"
//#include "api/generated/mqtt/testapi56client.h"
//#include "api/generated/mqtt/testapi57client.h"
//#include "api/generated/mqtt/testapi58client.h"
//#include "api/generated/mqtt/testapi59client.h"

//#include "api/generated/mqtt/testapi60client.h"
//#include "api/generated/mqtt/testapi61client.h"
//#include "api/generated/mqtt/testapi62client.h"
//#include "api/generated/mqtt/testapi63client.h"
//#include "api/generated/mqtt/testapi64client.h"
//#include "api/generated/mqtt/testapi65client.h"
//#include "api/generated/mqtt/testapi66client.h"
//#include "api/generated/mqtt/testapi67client.h"
//#include "api/generated/mqtt/testapi68client.h"
//#include "api/generated/mqtt/testapi69client.h"
//
//#include "api/generated/mqtt/testapi70client.h"
//#include "api/generated/mqtt/testapi71client.h"
//#include "api/generated/mqtt/testapi72client.h"
//#include "api/generated/mqtt/testapi73client.h"
//#include "api/generated/mqtt/testapi74client.h"
//#include "api/generated/mqtt/testapi75client.h"
//#include "api/generated/mqtt/testapi76client.h"
//#include "api/generated/mqtt/testapi77client.h"
//#include "api/generated/mqtt/testapi78client.h"
//#include "api/generated/mqtt/testapi79client.h"
//
//#include "api/generated/mqtt/testapi80client.h"
//#include "api/generated/mqtt/testapi81client.h"
//#include "api/generated/mqtt/testapi82client.h"
//#include "api/generated/mqtt/testapi83client.h"
//#include "api/generated/mqtt/testapi84client.h"
//#include "api/generated/mqtt/testapi85client.h"
//#include "api/generated/mqtt/testapi86client.h"
//#include "api/generated/mqtt/testapi87client.h"
//#include "api/generated/mqtt/testapi88client.h"
//#include "api/generated/mqtt/testapi89client.h"
//
//#include "api/generated/mqtt/testapi90client.h"
//#include "api/generated/mqtt/testapi91client.h"
//#include "api/generated/mqtt/testapi92client.h"
//#include "api/generated/mqtt/testapi93client.h"
//#include "api/generated/mqtt/testapi94client.h"
//#include "api/generated/mqtt/testapi95client.h"
//#include "api/generated/mqtt/testapi96client.h"
//#include "api/generated/mqtt/testapi97client.h"
//#include "api/generated/mqtt/testapi98client.h"
//#include "api/generated/mqtt/testapi99client.h"



template<class MqttInterface, class TestData, class FunctionSetter>
void addTestData(std::shared_ptr<ApiGear::MQTT::Client> client, std::vector<TestData>& elements, FunctionSetter& setter)
{
    TestData element;
    auto obj = std::make_shared<TestSink<MqttInterface>>(client);
    element.sink = obj;
    element.testFunction = [obj, &setter](const auto& value) {setter.testFunction(obj, value); };
    elements.push_back(element);
}

template<class TestData, class FunctionSetter>
std::vector<TestData> getTestData(FunctionSetter& setter, std::shared_ptr<ApiGear::MQTT::Client> client)
{
    std::vector<TestData> data;
    addTestData<Cpp::Api::MQTT::TestApi0Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi1Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi2Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi3Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi4Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi5Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi6Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi7Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi8Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi9Client, TestData, FunctionSetter>(client, data, setter);

    addTestData<Cpp::Api::MQTT::TestApi10Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi11Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi12Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi13Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi14Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi15Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi16Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi17Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi18Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi19Client, TestData, FunctionSetter>(client, data, setter);

    addTestData<Cpp::Api::MQTT::TestApi20Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi21Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi22Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi23Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi24Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi25Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi26Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi27Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi28Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi29Client, TestData, FunctionSetter>(client, data, setter);

    addTestData<Cpp::Api::MQTT::TestApi30Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi31Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi32Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi33Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi34Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi35Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi36Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi37Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi38Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi39Client, TestData, FunctionSetter>(client, data, setter);

    addTestData<Cpp::Api::MQTT::TestApi40Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi41Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi42Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi43Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi44Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi45Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi46Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi47Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi48Client, TestData, FunctionSetter>(client, data, setter);
    addTestData<Cpp::Api::MQTT::TestApi49Client, TestData, FunctionSetter>(client, data, setter);

    //addTestData<Cpp::Api::MQTT::TestApi50Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi51Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi52Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi53Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi54Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi55Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi56Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi57Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi58Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi59Client, TestData, FunctionSetter>(client, data, setter);

    //addTestData<Cpp::Api::MQTT::TestApi60Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi61Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi62Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi63Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi64Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi65Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi66Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi67Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi68Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi69Client, TestData, FunctionSetter>(client, data, setter);

    //addTestData<Cpp::Api::MQTT::TestApi70Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi71Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi72Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi73Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi74Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi75Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi76Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi77Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi78Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi79Client, TestData, FunctionSetter>(client, data, setter);

    //addTestData<Cpp::Api::MQTT::TestApi80Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi81Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi82Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi83Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi84Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi85Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi86Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi87Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi88Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi89Client, TestData, FunctionSetter>(client, data, setter);

    //addTestData<Cpp::Api::MQTT::TestApi90Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi91Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi92Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi93Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi94Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi95Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi96Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi97Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi98Client, TestData, FunctionSetter>(client, data, setter);
    //addTestData<Cpp::Api::MQTT::TestApi99Client, TestData, FunctionSetter>(client, data, setter);


    return data;
}
