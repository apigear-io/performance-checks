

#include "api/implementation/testapi43.h"
#include "api/generated/core/testapi43.publisher.h"
#include "api/generated/core/testapi43.data.h"

using namespace Cpp::Api;

TestApi43::TestApi43()
    : m_publisher(std::make_unique<TestApi43Publisher>())
{
}
TestApi43::~TestApi43()
{
}

void TestApi43::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi43::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi43::setPropFloat(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi43::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi43::setPropString(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi43::getPropString() const
{
    return m_data.m_propString;
}

int TestApi43::funcInt(int paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0;
}

std::future<int> TestApi43::funcIntAsync(int paramInt)
{
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            return funcInt(paramInt);
        }
    );
}

float TestApi43::funcFloat(float paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> TestApi43::funcFloatAsync(float paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat(paramFloat);
        }
    );
}

std::string TestApi43::funcString(const std::string& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::string();
}

std::future<std::string> TestApi43::funcStringAsync(const std::string& paramString)
{
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            return funcString(paramString);
        }
    );
}

ITestApi43Publisher& TestApi43::_getPublisher() const
{
    return *m_publisher;
}
