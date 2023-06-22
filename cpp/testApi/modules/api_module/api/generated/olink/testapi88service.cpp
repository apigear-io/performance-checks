

#include "api/generated/api/datastructs.api.h"
#include "api/generated/olink/testapi88service.h"
#include "api/generated/core/api.json.adapter.h"

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace Cpp::Api;
using namespace Cpp::Api::olink;

namespace 
{
const std::string interfaceId = "api.TestApi88";
}

TestApi88Service::TestApi88Service(std::shared_ptr<ITestApi88> TestApi88, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_TestApi88(TestApi88)
    , m_registry(registry)
{
    m_TestApi88->_getPublisher().subscribeToAllChanges(*this);
}

TestApi88Service::~TestApi88Service()
{
    m_TestApi88->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string TestApi88Service::olinkObjectName() {
    return interfaceId;
}

nlohmann::json TestApi88Service::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
    AG_LOG_DEBUG("TestApi88Service invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
    if(memberMethod == "funcInt") {
        const int& paramInt = fcnArgs.at(0);
        int result = m_TestApi88->funcInt(paramInt);
        return result;
    }
    if(memberMethod == "funcFloat") {
        const float& paramFloat = fcnArgs.at(0);
        float result = m_TestApi88->funcFloat(paramFloat);
        return result;
    }
    if(memberMethod == "funcString") {
        const std::string& paramString = fcnArgs.at(0);
        std::string result = m_TestApi88->funcString(paramString);
        return result;
    }
    return nlohmann::json();
}

void TestApi88Service::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("TestApi88Service set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
    if(memberProperty == "propInt") {
        int propInt = value.get<int>();
        m_TestApi88->setPropInt(propInt);
    }
    if(memberProperty == "propFloat") {
        float propFloat = value.get<float>();
        m_TestApi88->setPropFloat(propFloat);
    }
    if(memberProperty == "propString") {
        std::string propString = value.get<std::string>();
        m_TestApi88->setPropString(propString);
    } 
}

void TestApi88Service::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("TestApi88Service linked " + objectId);
}

void TestApi88Service::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("TestApi88Service unlinked " + objectId);
}

nlohmann::json TestApi88Service::olinkCollectProperties()
{
    return nlohmann::json::object({
        { "propInt", m_TestApi88->getPropInt() },
        { "propFloat", m_TestApi88->getPropFloat() },
        { "propString", m_TestApi88->getPropString() }
    });
}
void TestApi88Service::onSigInt(int paramInt)
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
void TestApi88Service::onSigFloat(float paramFloat)
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
void TestApi88Service::onSigString(const std::string& paramString)
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
void TestApi88Service::onPropIntChanged(int propInt)
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
void TestApi88Service::onPropFloatChanged(float propFloat)
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
void TestApi88Service::onPropStringChanged(const std::string& propString)
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

