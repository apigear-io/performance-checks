

#include "api/generated/olink/testapi36client.h"
#include "api/generated/core/testapi36.publisher.h"
#include "api/generated/core/api.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Cpp::Api;
using namespace Cpp::Api::olink;

namespace 
{
const std::string interfaceId = "api.TestApi36";
}

TestApi36Client::TestApi36Client()
    : m_publisher(std::make_unique<TestApi36Publisher>())
{}

void TestApi36Client::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("propInt")) {
        setPropIntLocal(fields["propInt"].get<int>());
    }
    if(fields.contains("propFloat")) {
        setPropFloatLocal(fields["propFloat"].get<float>());
    }
    if(fields.contains("propString")) {
        setPropStringLocal(fields["propString"].get<std::string>());
    }
}

void TestApi36Client::setPropInt(int propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void TestApi36Client::setPropIntLocal(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi36Client::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi36Client::setPropFloat(float propFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    m_node->setRemoteProperty(propertyId, propFloat);
}

void TestApi36Client::setPropFloatLocal(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi36Client::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi36Client::setPropString(const std::string& propString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    m_node->setRemoteProperty(propertyId, propString);
}

void TestApi36Client::setPropStringLocal(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi36Client::getPropString() const
{
    return m_data.m_propString;
}

int TestApi36Client::funcInt(int paramInt)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return 0;
    }
    int value(funcIntAsync(paramInt).get());
    return value;
}

std::future<int> TestApi36Client::funcIntAsync(int paramInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<int>{};
    }
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            std::promise<int> resultPromise;
            static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcInt");
            m_node->invokeRemote(operationId,
                nlohmann::json::array({paramInt}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const int& value = arg.value.get<int>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

float TestApi36Client::funcFloat(float paramFloat)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return 0.0f;
    }
    float value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<float> TestApi36Client::funcFloatAsync(float paramFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<float>{};
    }
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            std::promise<float> resultPromise;
            static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcFloat");
            m_node->invokeRemote(operationId,
                nlohmann::json::array({paramFloat}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const float& value = arg.value.get<float>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

std::string TestApi36Client::funcString(const std::string& paramString)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::string();
    }
    std::string value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::string> TestApi36Client::funcStringAsync(const std::string& paramString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<std::string>{};
    }
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            std::promise<std::string> resultPromise;
            static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "funcString");
            m_node->invokeRemote(operationId,
                nlohmann::json::array({paramString}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const std::string& value = arg.value.get<std::string>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

std::string TestApi36Client::olinkObjectName()
{
    return interfaceId;
}

void TestApi36Client::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
    if(signalName == "sigInt") {
        m_publisher->publishSigInt(args[0].get<int>());   
        return;
    }
    if(signalName == "sigFloat") {
        m_publisher->publishSigFloat(args[0].get<float>());   
        return;
    }
    if(signalName == "sigString") {
        m_publisher->publishSigString(args[0].get<std::string>());   
        return;
    }
}

void TestApi36Client::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyState({ {ApiGear::ObjectLink::Name::getMemberName(propertyId), value} });
}
void TestApi36Client::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void TestApi36Client::olinkOnRelease()
{
    m_node = nullptr;
}

bool TestApi36Client::isReady() const
{
    return m_node != nullptr;
}

ITestApi36Publisher& TestApi36Client::_getPublisher() const
{
    return *m_publisher;
}
