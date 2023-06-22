

#include "api/implementation/testapi89.h"
#include "api/generated/core/testapi89.publisher.h"
#include "api/generated/core/testapi89.data.h"

using namespace Cpp::Api;

TestApi89::TestApi89()
    : m_publisher(std::make_unique<TestApi89Publisher>())
{
}
TestApi89::~TestApi89()
{
}

void TestApi89::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi89::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi89::setPropFloat(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi89::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi89::setPropString(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi89::getPropString() const
{
    return m_data.m_propString;
}

int TestApi89::funcInt(int paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0;
}

std::future<int> TestApi89::funcIntAsync(int paramInt)
{
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            return funcInt(paramInt);
        }
    );
}

float TestApi89::funcFloat(float paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> TestApi89::funcFloatAsync(float paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat(paramFloat);
        }
    );
}

std::string TestApi89::funcString(const std::string& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::string();
}

std::future<std::string> TestApi89::funcStringAsync(const std::string& paramString)
{
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            return funcString(paramString);
        }
    );
}

ITestApi89Publisher& TestApi89::_getPublisher() const
{
    return *m_publisher;
}
