

#include "api/implementation/testapi86.h"
#include "api/generated/core/testapi86.publisher.h"
#include "api/generated/core/testapi86.data.h"

using namespace Cpp::Api;

TestApi86::TestApi86()
    : m_publisher(std::make_unique<TestApi86Publisher>())
{
}
TestApi86::~TestApi86()
{
}

void TestApi86::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi86::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi86::setPropFloat(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi86::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi86::setPropString(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi86::getPropString() const
{
    return m_data.m_propString;
}

int TestApi86::funcInt(int paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0;
}

std::future<int> TestApi86::funcIntAsync(int paramInt)
{
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            return funcInt(paramInt);
        }
    );
}

float TestApi86::funcFloat(float paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> TestApi86::funcFloatAsync(float paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat(paramFloat);
        }
    );
}

std::string TestApi86::funcString(const std::string& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::string();
}

std::future<std::string> TestApi86::funcStringAsync(const std::string& paramString)
{
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            return funcString(paramString);
        }
    );
}

ITestApi86Publisher& TestApi86::_getPublisher() const
{
    return *m_publisher;
}
