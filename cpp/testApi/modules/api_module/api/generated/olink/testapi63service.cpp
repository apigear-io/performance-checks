

#include "api/generated/api/datastructs.api.h"
#include "api/generated/olink/testapi63service.h"
#include "api/generated/core/api.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Cpp::Api;
using namespace Cpp::Api::olink;

namespace 
{
const std::string interfaceId = "api.TestApi63";
}

TestApi63Service::TestApi63Service(std::shared_ptr<ITestApi63> TestApi63, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_TestApi63(TestApi63)
    , m_registry(registry)
{
    m_TestApi63->_getPublisher().subscribeToAllChanges(*this);
}

TestApi63Service::~TestApi63Service()
{
    m_TestApi63->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string TestApi63Service::olinkObjectName() {
    return interfaceId;
}

nlohmann::json TestApi63Service::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("TestApi63Service invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcInt") {
        const int& paramInt = fcnArgs.at(0);
        int result = m_TestApi63->funcInt(paramInt);
        return result;
    }
    if(memberMethod == "funcFloat") {
        const float& paramFloat = fcnArgs.at(0);
        float result = m_TestApi63->funcFloat(paramFloat);
        return result;
    }
    if(memberMethod == "funcString") {
        const std::string& paramString = fcnArgs.at(0);
        std::string result = m_TestApi63->funcString(paramString);
        return result;
    }
    return nlohmann::json();
}

void TestApi63Service::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("TestApi63Service set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propInt") {
        int propInt = value.get<int>();
        m_TestApi63->setPropInt(propInt);
    }
    if(memberProperty == "propFloat") {
        float propFloat = value.get<float>();
        m_TestApi63->setPropFloat(propFloat);
    }
    if(memberProperty == "propString") {
        std::string propString = value.get<std::string>();
        m_TestApi63->setPropString(propString);
    } 
}

void TestApi63Service::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("TestApi63Service linked " + objectId);
}

void TestApi63Service::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("TestApi63Service unlinked " + objectId);
}

nlohmann::json TestApi63Service::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propInt", m_TestApi63->getPropInt() },
        { "propFloat", m_TestApi63->getPropFloat() },
        { "propString", m_TestApi63->getPropString() }
    });
}
void TestApi63Service::onSigInt(int paramInt)
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
void TestApi63Service::onSigFloat(float paramFloat)
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
void TestApi63Service::onSigString(const std::string& paramString)
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
void TestApi63Service::onPropIntChanged(int propInt)
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
void TestApi63Service::onPropFloatChanged(float propFloat)
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
void TestApi63Service::onPropStringChanged(const std::string& propString)
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

