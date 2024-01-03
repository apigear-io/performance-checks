#pragma once
#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <future>
#include <vector>
#include "itestsink.h"

#include "api/mqtt/mqtttestapi0.h"
#include "api/mqtt/mqtttestapi1.h"
#include "api/mqtt/mqtttestapi2.h"
#include "api/mqtt/mqtttestapi3.h"
#include "api/mqtt/mqtttestapi4.h"
#include "api/mqtt/mqtttestapi5.h"
#include "api/mqtt/mqtttestapi6.h"
#include "api/mqtt/mqtttestapi7.h"
#include "api/mqtt/mqtttestapi8.h"
#include "api/mqtt/mqtttestapi9.h"

#include "api/mqtt/mqtttestapi10.h"
#include "api/mqtt/mqtttestapi11.h"
#include "api/mqtt/mqtttestapi12.h"
#include "api/mqtt/mqtttestapi13.h"
#include "api/mqtt/mqtttestapi14.h"
#include "api/mqtt/mqtttestapi15.h"
#include "api/mqtt/mqtttestapi16.h"
#include "api/mqtt/mqtttestapi17.h"
#include "api/mqtt/mqtttestapi18.h"
#include "api/mqtt/mqtttestapi19.h"

#include "api/mqtt/mqtttestapi20.h"
#include "api/mqtt/mqtttestapi21.h"
#include "api/mqtt/mqtttestapi22.h"
#include "api/mqtt/mqtttestapi23.h"
#include "api/mqtt/mqtttestapi24.h"
#include "api/mqtt/mqtttestapi25.h"
#include "api/mqtt/mqtttestapi26.h"
#include "api/mqtt/mqtttestapi27.h"
#include "api/mqtt/mqtttestapi28.h"
#include "api/mqtt/mqtttestapi29.h"

#include "api/mqtt/mqtttestapi30.h"
#include "api/mqtt/mqtttestapi31.h"
#include "api/mqtt/mqtttestapi32.h"
#include "api/mqtt/mqtttestapi33.h"
#include "api/mqtt/mqtttestapi34.h"
#include "api/mqtt/mqtttestapi35.h"
#include "api/mqtt/mqtttestapi36.h"
#include "api/mqtt/mqtttestapi37.h"
#include "api/mqtt/mqtttestapi38.h"
#include "api/mqtt/mqtttestapi39.h"

#include "api/mqtt/mqtttestapi40.h"
#include "api/mqtt/mqtttestapi41.h"
#include "api/mqtt/mqtttestapi42.h"
#include "api/mqtt/mqtttestapi43.h"
#include "api/mqtt/mqtttestapi44.h"
#include "api/mqtt/mqtttestapi45.h"
#include "api/mqtt/mqtttestapi46.h"
#include "api/mqtt/mqtttestapi47.h"
#include "api/mqtt/mqtttestapi48.h"
#include "api/mqtt/mqtttestapi49.h"

#include "api/mqtt/mqtttestapi50.h"
#include "api/mqtt/mqtttestapi51.h"
#include "api/mqtt/mqtttestapi52.h"
#include "api/mqtt/mqtttestapi53.h"
#include "api/mqtt/mqtttestapi54.h"
#include "api/mqtt/mqtttestapi55.h"
#include "api/mqtt/mqtttestapi56.h"
#include "api/mqtt/mqtttestapi57.h"
#include "api/mqtt/mqtttestapi58.h"
#include "api/mqtt/mqtttestapi59.h"

#include "api/mqtt/mqtttestapi60.h"
#include "api/mqtt/mqtttestapi61.h"
#include "api/mqtt/mqtttestapi62.h"
#include "api/mqtt/mqtttestapi63.h"
#include "api/mqtt/mqtttestapi64.h"
#include "api/mqtt/mqtttestapi65.h"
#include "api/mqtt/mqtttestapi66.h"
#include "api/mqtt/mqtttestapi67.h"
#include "api/mqtt/mqtttestapi68.h"
#include "api/mqtt/mqtttestapi69.h"

#include "api/mqtt/mqtttestapi70.h"
#include "api/mqtt/mqtttestapi71.h"
#include "api/mqtt/mqtttestapi72.h"
#include "api/mqtt/mqtttestapi73.h"
#include "api/mqtt/mqtttestapi74.h"
#include "api/mqtt/mqtttestapi75.h"
#include "api/mqtt/mqtttestapi76.h"
#include "api/mqtt/mqtttestapi77.h"
#include "api/mqtt/mqtttestapi78.h"
#include "api/mqtt/mqtttestapi79.h"

#include "api/mqtt/mqtttestapi80.h"
#include "api/mqtt/mqtttestapi81.h"
#include "api/mqtt/mqtttestapi82.h"
#include "api/mqtt/mqtttestapi83.h"
#include "api/mqtt/mqtttestapi84.h"
#include "api/mqtt/mqtttestapi85.h"
#include "api/mqtt/mqtttestapi86.h"
#include "api/mqtt/mqtttestapi87.h"
#include "api/mqtt/mqtttestapi88.h"
#include "api/mqtt/mqtttestapi89.h"

#include "api/mqtt/mqtttestapi90.h"
#include "api/mqtt/mqtttestapi91.h"
#include "api/mqtt/mqtttestapi92.h"
#include "api/mqtt/mqtttestapi93.h"
#include "api/mqtt/mqtttestapi94.h"
#include "api/mqtt/mqtttestapi95.h"
#include "api/mqtt/mqtttestapi96.h"
#include "api/mqtt/mqtttestapi97.h"
#include "api/mqtt/mqtttestapi98.h"
#include "api/mqtt/mqtttestapi99.h"



template<class MqttInterface, class BaseInterface, class TestData, class FunctionSetter>
void addTestData(ApiGear::Mqtt::Client& client, std::vector<TestData>& elements, FunctionSetter& setter)
{
    TestData element;
    auto obj =  std::make_shared<TestSink<MqttInterface,BaseInterface>>(client);
    element.sink = obj;
    element.testFunction = [obj, &setter](const auto& value) {setter.testFunction(obj, value); };
    elements.push_back(element);
}

template<class TestData, class FunctionSetter>
std::vector<TestData> getTestData(FunctionSetter& setter, ApiGear::Mqtt::Client& client)
{
    std::vector<TestData> data;
    addTestData<api::MqttTestApi0, api::AbstractTestApi0, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi1, api::AbstractTestApi1, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi2, api::AbstractTestApi2, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi3, api::AbstractTestApi3, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi4, api::AbstractTestApi4, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi5, api::AbstractTestApi5, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi6, api::AbstractTestApi6, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi7, api::AbstractTestApi7, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi8, api::AbstractTestApi8, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi9, api::AbstractTestApi9, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi10, api::AbstractTestApi10, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi11, api::AbstractTestApi11, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi12, api::AbstractTestApi12, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi13, api::AbstractTestApi13, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi14, api::AbstractTestApi14, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi15, api::AbstractTestApi15, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi16, api::AbstractTestApi16, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi17, api::AbstractTestApi17, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi18, api::AbstractTestApi18, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi19, api::AbstractTestApi19, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi20, api::AbstractTestApi20, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi21, api::AbstractTestApi21, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi22, api::AbstractTestApi22, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi23, api::AbstractTestApi23, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi24, api::AbstractTestApi24, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi25, api::AbstractTestApi25, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi26, api::AbstractTestApi26, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi27, api::AbstractTestApi27, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi28, api::AbstractTestApi28, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi29, api::AbstractTestApi29, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi30, api::AbstractTestApi30, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi31, api::AbstractTestApi31, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi32, api::AbstractTestApi32, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi33, api::AbstractTestApi33, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi34, api::AbstractTestApi34, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi35, api::AbstractTestApi35, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi36, api::AbstractTestApi36, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi37, api::AbstractTestApi37, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi38, api::AbstractTestApi38, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi39, api::AbstractTestApi39, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi40, api::AbstractTestApi40, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi41, api::AbstractTestApi41, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi42, api::AbstractTestApi42, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi43, api::AbstractTestApi43, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi44, api::AbstractTestApi44, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi45, api::AbstractTestApi45, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi46, api::AbstractTestApi46, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi47, api::AbstractTestApi47, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi48, api::AbstractTestApi48, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi49, api::AbstractTestApi49, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi50, api::AbstractTestApi50, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi51, api::AbstractTestApi51, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi52, api::AbstractTestApi52, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi53, api::AbstractTestApi53, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi54, api::AbstractTestApi54, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi55, api::AbstractTestApi55, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi56, api::AbstractTestApi56, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi57, api::AbstractTestApi57, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi58, api::AbstractTestApi58, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi59, api::AbstractTestApi59, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi60, api::AbstractTestApi60, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi61, api::AbstractTestApi61, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi62, api::AbstractTestApi62, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi63, api::AbstractTestApi63, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi64, api::AbstractTestApi64, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi65, api::AbstractTestApi65, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi66, api::AbstractTestApi66, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi67, api::AbstractTestApi67, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi68, api::AbstractTestApi68, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi69, api::AbstractTestApi69, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi70, api::AbstractTestApi70, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi71, api::AbstractTestApi71, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi72, api::AbstractTestApi72, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi73, api::AbstractTestApi73, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi74, api::AbstractTestApi74, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi75, api::AbstractTestApi75, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi76, api::AbstractTestApi76, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi77, api::AbstractTestApi77, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi78, api::AbstractTestApi78, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi79, api::AbstractTestApi79, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi80, api::AbstractTestApi80, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi81, api::AbstractTestApi81, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi82, api::AbstractTestApi82, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi83, api::AbstractTestApi83, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi84, api::AbstractTestApi84, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi85, api::AbstractTestApi85, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi86, api::AbstractTestApi86, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi87, api::AbstractTestApi87, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi88, api::AbstractTestApi88, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi89, api::AbstractTestApi89, TestData, FunctionSetter>(client, data, setter);

    addTestData<api::MqttTestApi90, api::AbstractTestApi90, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi91, api::AbstractTestApi91, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi92, api::AbstractTestApi92, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi93, api::AbstractTestApi93, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi94, api::AbstractTestApi94, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi95, api::AbstractTestApi95, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi96, api::AbstractTestApi96, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi97, api::AbstractTestApi97, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi98, api::AbstractTestApi98, TestData, FunctionSetter>(client, data, setter);
    addTestData<api::MqttTestApi99, api::AbstractTestApi99, TestData, FunctionSetter>(client, data, setter);


    return data;
}
