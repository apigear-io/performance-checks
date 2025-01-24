

#include "api/implementation/testapi0.h"
#include "api/generated/core/testapi0.publisher.h"
#include "api/generated/core/testapi0.data.h"

using namespace Cpp::Api;

TestApi0::TestApi0()
    : m_publisher(std::make_unique<TestApi0Publisher>())
{
}
TestApi0::~TestApi0()
{
}

void TestApi0::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi0::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi0::setPropFloat(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi0::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi0::setPropString(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi0::getPropString() const
{
    return m_data.m_propString;
}

int TestApi0::funcInt(int paramInt)
{
    return paramInt; 
}

std::future<int> TestApi0::funcIntAsync(int paramInt, std::function<void(int)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramInt]()
        {auto result = funcInt(paramInt);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

float TestApi0::funcFloat(float paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> TestApi0::funcFloatAsync(float paramFloat, std::function<void(float)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramFloat]()
        {auto result = funcFloat(paramFloat);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

std::string TestApi0::funcString(const std::string& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::string();
}

std::future<std::string> TestApi0::funcStringAsync(const std::string& paramString, std::function<void(std::string)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramString]()
        {auto result = funcString(paramString);
            if (callback)
            {
                callback(result);
            }return result;
        }
    );
}

void TestApi0::funcVoid(int paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
}

std::future<void> TestApi0::funcVoidAsync(int paramInt, std::function<void(void)> callback)
{
    return std::async(std::launch::async, [this, callback,
                    paramInt]()
        {funcVoid(paramInt);
            if (callback)
            {
                callback();
            }
        }
    );
}

ITestApi0Publisher& TestApi0::_getPublisher() const
{
    return *m_publisher;
}
