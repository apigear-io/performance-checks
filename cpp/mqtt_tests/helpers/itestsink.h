#pragma once

#include <apigear/mqtt/mqttclient.h>

class ITestSink
{
public:
    virtual bool isReady() const = 0;
    virtual uint32_t receivedMessages() const = 0;
};


template <class BaseMqttTestApi>
class TestSink : public ITestSink, public BaseMqttTestApi
{
public:
    TestSink(std::shared_ptr<ApiGear::MQTT::Client> client)
        :BaseMqttTestApi(client)
    {
        idPropInt = BaseMqttTestApi::_getPublisher().subscribeToPropIntChanged([this](auto value) {
            msgReceived++; 
            });
        idPropFloat = BaseMqttTestApi::_getPublisher().subscribeToPropFloatChanged([this](auto value) {msgReceived++; });
        idPropString = BaseMqttTestApi::_getPublisher().subscribeToPropStringChanged([this](auto value) {msgReceived++; });
        idSigInt = BaseMqttTestApi::_getPublisher().subscribeToSigInt([this](auto value) {msgReceived++; });
        idSigFloat = BaseMqttTestApi::_getPublisher().subscribeToSigFloat([this](auto value) {msgReceived++; });
        idSigString = BaseMqttTestApi::_getPublisher().subscribeToSigString([this](auto value) {msgReceived++; });
    }

    ~TestSink()
    {
        BaseMqttTestApi::_getPublisher().unsubscribeFromPropIntChanged(idPropInt);
        BaseMqttTestApi::_getPublisher().unsubscribeFromPropFloatChanged(idPropFloat);
        BaseMqttTestApi::_getPublisher().unsubscribeFromPropStringChanged(idPropString);
        BaseMqttTestApi::_getPublisher().unsubscribeFromSigInt(idSigInt);
        BaseMqttTestApi::_getPublisher().unsubscribeFromSigFloat(idSigFloat);
        BaseMqttTestApi::_getPublisher().unsubscribeFromSigString(idSigString);
    }

    bool isReady() const override
    {
        return BaseMqttTestApi::isReady();
    }

    uint32_t receivedMessages() const override
    {
        return msgReceived;
    }
private:
    long idPropInt;
    long idPropFloat;
    long idPropString;
    long idSigInt;
    long idSigFloat;
    long idSigString;
    uint32_t msgReceived = 0;
};
