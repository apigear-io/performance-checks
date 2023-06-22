#pragma once
#include "inspected_sink.h"
#include "olink/clientnode.h"
#include "olink/clientregistry.h"
#include "olink/core/types.h"
#include "apigear/olink/olinkconnection.h"
#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <future>

#include "api/generated/olink/testapi0client.h"
#include "api/generated/olink/testapi1client.h"
#include "api/generated/olink/testapi2client.h"
#include "api/generated/olink/testapi3client.h"
#include "api/generated/olink/testapi4client.h"
#include "api/generated/olink/testapi5client.h"
#include "api/generated/olink/testapi6client.h"
#include "api/generated/olink/testapi7client.h"
#include "api/generated/olink/testapi8client.h"
#include "api/generated/olink/testapi9client.h"

#include "api/generated/olink/testapi10client.h"
#include "api/generated/olink/testapi11client.h"
#include "api/generated/olink/testapi12client.h"
#include "api/generated/olink/testapi13client.h"
#include "api/generated/olink/testapi14client.h"
#include "api/generated/olink/testapi15client.h"
#include "api/generated/olink/testapi16client.h"
#include "api/generated/olink/testapi17client.h"
#include "api/generated/olink/testapi18client.h"
#include "api/generated/olink/testapi19client.h"

#include "api/generated/olink/testapi20client.h"
#include "api/generated/olink/testapi21client.h"
#include "api/generated/olink/testapi22client.h"
#include "api/generated/olink/testapi23client.h"
#include "api/generated/olink/testapi24client.h"
#include "api/generated/olink/testapi25client.h"
#include "api/generated/olink/testapi26client.h"
#include "api/generated/olink/testapi27client.h"
#include "api/generated/olink/testapi28client.h"
#include "api/generated/olink/testapi29client.h"

#include "api/generated/olink/testapi30client.h"
#include "api/generated/olink/testapi31client.h"
#include "api/generated/olink/testapi32client.h"
#include "api/generated/olink/testapi33client.h"
#include "api/generated/olink/testapi34client.h"
#include "api/generated/olink/testapi35client.h"
#include "api/generated/olink/testapi36client.h"
#include "api/generated/olink/testapi37client.h"
#include "api/generated/olink/testapi38client.h"
#include "api/generated/olink/testapi39client.h"

#include "api/generated/olink/testapi40client.h"
#include "api/generated/olink/testapi41client.h"
#include "api/generated/olink/testapi42client.h"
#include "api/generated/olink/testapi43client.h"
#include "api/generated/olink/testapi44client.h"
#include "api/generated/olink/testapi45client.h"
#include "api/generated/olink/testapi46client.h"
#include "api/generated/olink/testapi47client.h"
#include "api/generated/olink/testapi48client.h"
#include "api/generated/olink/testapi49client.h"

#include "api/generated/olink/testapi50client.h"
#include "api/generated/olink/testapi51client.h"
#include "api/generated/olink/testapi52client.h"
#include "api/generated/olink/testapi53client.h"
#include "api/generated/olink/testapi54client.h"
#include "api/generated/olink/testapi55client.h"
#include "api/generated/olink/testapi56client.h"
#include "api/generated/olink/testapi57client.h"
#include "api/generated/olink/testapi58client.h"
#include "api/generated/olink/testapi59client.h"

#include "api/generated/olink/testapi60client.h"
#include "api/generated/olink/testapi61client.h"
#include "api/generated/olink/testapi62client.h"
#include "api/generated/olink/testapi63client.h"
#include "api/generated/olink/testapi64client.h"
#include "api/generated/olink/testapi65client.h"
#include "api/generated/olink/testapi66client.h"
#include "api/generated/olink/testapi67client.h"
#include "api/generated/olink/testapi68client.h"
#include "api/generated/olink/testapi69client.h"

#include "api/generated/olink/testapi70client.h"
#include "api/generated/olink/testapi71client.h"
#include "api/generated/olink/testapi72client.h"
#include "api/generated/olink/testapi73client.h"
#include "api/generated/olink/testapi74client.h"
#include "api/generated/olink/testapi75client.h"
#include "api/generated/olink/testapi76client.h"
#include "api/generated/olink/testapi77client.h"
#include "api/generated/olink/testapi78client.h"
#include "api/generated/olink/testapi79client.h"

#include "api/generated/olink/testapi80client.h"
#include "api/generated/olink/testapi81client.h"
#include "api/generated/olink/testapi82client.h"
#include "api/generated/olink/testapi83client.h"
#include "api/generated/olink/testapi84client.h"
#include "api/generated/olink/testapi85client.h"
#include "api/generated/olink/testapi86client.h"
#include "api/generated/olink/testapi87client.h"
#include "api/generated/olink/testapi88client.h"
#include "api/generated/olink/testapi89client.h"

#include "api/generated/olink/testapi90client.h"
#include "api/generated/olink/testapi91client.h"
#include "api/generated/olink/testapi92client.h"
#include "api/generated/olink/testapi93client.h"
#include "api/generated/olink/testapi94client.h"
#include "api/generated/olink/testapi95client.h"
#include "api/generated/olink/testapi96client.h"
#include "api/generated/olink/testapi97client.h"
#include "api/generated/olink/testapi98client.h"
#include "api/generated/olink/testapi99client.h"


template<class Interface, class TestData, class FunctionSetter>
void addTestData(std::shared_ptr<Interface> olinkClient, std::vector<TestData>& elements, FunctionSetter& setter)
{
    TestData element;
    element.sink = std::make_shared<InspectedSink>(olinkClient);
    element.testFunction = [olinkClient, &setter](const auto& value) {setter.testFunction(olinkClient, value); };
    elements.push_back(element);
}

template<class TestData, class FunctionSetter>
std::vector<TestData> getTestData(FunctionSetter& setter)
{
    std::vector<TestData> data;
    addTestData(std::make_shared<Cpp::Api::olink::TestApi0Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi1Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi2Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi3Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi4Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi5Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi6Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi7Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi8Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi9Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi10Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi11Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi12Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi13Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi14Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi15Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi16Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi17Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi18Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi19Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi20Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi21Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi22Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi23Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi24Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi25Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi26Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi27Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi28Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi29Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi30Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi31Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi32Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi33Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi34Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi35Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi36Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi37Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi38Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi39Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi40Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi41Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi42Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi43Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi44Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi45Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi46Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi47Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi48Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi49Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi50Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi51Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi52Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi53Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi54Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi55Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi56Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi57Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi58Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi59Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi60Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi61Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi62Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi63Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi64Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi65Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi66Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi67Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi68Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi69Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi70Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi71Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi72Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi73Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi74Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi75Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi76Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi77Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi78Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi79Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi80Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi81Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi82Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi83Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi84Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi85Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi86Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi87Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi88Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi89Client>(), data, setter);

    addTestData(std::make_shared<Cpp::Api::olink::TestApi90Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi91Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi92Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi93Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi94Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi95Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi96Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi97Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi98Client>(), data, setter);
    addTestData(std::make_shared<Cpp::Api::olink::TestApi99Client>(), data, setter);


    return data;
}
