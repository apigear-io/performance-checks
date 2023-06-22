

#include "api/generated/olink/testapi0client.h"
#include "api/generated/core/testapi0.publisher.h"
#include "api/generated/core/api.json.adapter.h"

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace Cpp::Api;
using namespace Cpp::Api::olink;

namespace 
{
const std::string interfaceId = "api.TestApi0";
}

TestApi0Client::TestApi0Client()
    : m_publisher(std::make_unique<TestApi0Publisher>())
{}

void TestApi0Client::applyState(const nlohmann::json& fields) 
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

void TestApi0Client::setPropInt(int propInt)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
    m_node->setRemoteProperty(propertyId, propInt);
}

void TestApi0Client::setPropIntLocal(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi0Client::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi0Client::setPropFloat(float propFloat)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
    m_node->setRemoteProperty(propertyId, propFloat);
}

void TestApi0Client::setPropFloatLocal(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi0Client::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi0Client::setPropString(const std::string& propString)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
    m_node->setRemoteProperty(propertyId, propString);
}

void TestApi0Client::setPropStringLocal(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi0Client::getPropString() const
{
    return m_data.m_propString;
}

int TestApi0Client::funcInt(int paramInt)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return 0;
    }
    int value(funcIntAsync(paramInt).get());
    return value;
}

std::future<int> TestApi0Client::funcIntAsync(int paramInt)
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

float TestApi0Client::funcFloat(float paramFloat)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return 0.0f;
    }
    float value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<float> TestApi0Client::funcFloatAsync(float paramFloat)
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

std::string TestApi0Client::funcString(const std::string& paramString)
{
     if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::string();
    }
    std::string value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::string> TestApi0Client::funcStringAsync(const std::string& paramString)
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

std::string TestApi0Client::olinkObjectName()
{
    return interfaceId;
}

void TestApi0Client::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
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

void TestApi0Client::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyState({ {ApiGear::ObjectLink::Name::getMemberName(propertyId), value} });
}
void TestApi0Client::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void TestApi0Client::olinkOnRelease()
{
    m_node = nullptr;
}

bool TestApi0Client::isReady() const
{
    return m_node != nullptr;
}

ITestApi0Publisher& TestApi0Client::_getPublisher() const
{
    return *m_publisher;
}
