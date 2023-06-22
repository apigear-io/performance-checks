

#include "api/generated/api/datastructs.api.h"
#include "api/generated/olink/testapi15service.h"
#include "api/generated/core/api.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Cpp::Api;
using namespace Cpp::Api::olink;

namespace 
{
const std::string interfaceId = "api.TestApi15";
}

TestApi15Service::TestApi15Service(std::shared_ptr<ITestApi15> TestApi15, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_TestApi15(TestApi15)
    , m_registry(registry)
{
    m_TestApi15->_getPublisher().subscribeToAllChanges(*this);
}

TestApi15Service::~TestApi15Service()
{
    m_TestApi15->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string TestApi15Service::olinkObjectName() {
    return interfaceId;
}

nlohmann::json TestApi15Service::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("TestApi15Service invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcInt") {
        const int& paramInt = fcnArgs.at(0);
        int result = m_TestApi15->funcInt(paramInt);
        return result;
    }
    if(memberMethod == "funcFloat") {
        const float& paramFloat = fcnArgs.at(0);
        float result = m_TestApi15->funcFloat(paramFloat);
        return result;
    }
    if(memberMethod == "funcString") {
        const std::string& paramString = fcnArgs.at(0);
        std::string result = m_TestApi15->funcString(paramString);
        return result;
    }
    return nlohmann::json();
}

void TestApi15Service::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("TestApi15Service set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propInt") {
        int propInt = value.get<int>();
        m_TestApi15->setPropInt(propInt);
    }
    if(memberProperty == "propFloat") {
        float propFloat = value.get<float>();
        m_TestApi15->setPropFloat(propFloat);
    }
    if(memberProperty == "propString") {
        std::string propString = value.get<std::string>();
        m_TestApi15->setPropString(propString);
    } 
}

void TestApi15Service::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("TestApi15Service linked " + objectId);
}

void TestApi15Service::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("TestApi15Service unlinked " + objectId);
}

nlohmann::json TestApi15Service::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propInt", m_TestApi15->getPropInt() },
        { "propFloat", m_TestApi15->getPropFloat() },
        { "propString", m_TestApi15->getPropString() }
    });
}
void TestApi15Service::onSigInt(int paramInt)
{
    const nlohmann::json args = { paramInt };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigInt");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void TestApi15Service::onSigFloat(float paramFloat)
{
    const nlohmann::json args = { paramFloat };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigFloat");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void TestApi15Service::onSigString(const std::string& paramString)
{
    const nlohmann::json args = { paramString };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigString");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
void TestApi15Service::onPropIntChanged(int propInt)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propInt);
        }
    }
}
void TestApi15Service::onPropFloatChanged(float propFloat)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propFloat);
        }
    }
}
void TestApi15Service::onPropStringChanged(const std::string& propString)
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, propString);
        }
    }
}

