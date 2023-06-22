

#include "api/implementation/testapi31.h"
#include "api/generated/core/testapi31.publisher.h"
#include "api/generated/core/testapi31.data.h"

using namespace Cpp::Api;

TestApi31::TestApi31()
    : m_publisher(std::make_unique<TestApi31Publisher>())
{
}
TestApi31::~TestApi31()
{
}

void TestApi31::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi31::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi31::setPropFloat(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi31::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi31::setPropString(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi31::getPropString() const
{
    return m_data.m_propString;
}

int TestApi31::funcInt(int paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0;
}

std::future<int> TestApi31::funcIntAsync(int paramInt)
{
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            return funcInt(paramInt);
        }
    );
}

float TestApi31::funcFloat(float paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> TestApi31::funcFloatAsync(float paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat(paramFloat);
        }
    );
}

std::string TestApi31::funcString(const std::string& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::string();
}

std::future<std::string> TestApi31::funcStringAsync(const std::string& paramString)
{
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            return funcString(paramString);
        }
    );
}

ITestApi31Publisher& TestApi31::_getPublisher() const
{
    return *m_publisher;
}
