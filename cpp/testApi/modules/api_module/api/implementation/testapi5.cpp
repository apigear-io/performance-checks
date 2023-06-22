

#include "api/implementation/testapi5.h"
#include "api/generated/core/testapi5.publisher.h"
#include "api/generated/core/testapi5.data.h"

using namespace Cpp::Api;

TestApi5::TestApi5()
    : m_publisher(std::make_unique<TestApi5Publisher>())
{
}
TestApi5::~TestApi5()
{
}

void TestApi5::setPropInt(int propInt)
{
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

int TestApi5::getPropInt() const
{
    return m_data.m_propInt;
}

void TestApi5::setPropFloat(float propFloat)
{
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

float TestApi5::getPropFloat() const
{
    return m_data.m_propFloat;
}

void TestApi5::setPropString(const std::string& propString)
{
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::string& TestApi5::getPropString() const
{
    return m_data.m_propString;
}

int TestApi5::funcInt(int paramInt)
{
    (void) paramInt; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0;
}

std::future<int> TestApi5::funcIntAsync(int paramInt)
{
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            return funcInt(paramInt);
        }
    );
}

float TestApi5::funcFloat(float paramFloat)
{
    (void) paramFloat; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return 0.0f;
}

std::future<float> TestApi5::funcFloatAsync(float paramFloat)
{
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            return funcFloat(paramFloat);
        }
    );
}

std::string TestApi5::funcString(const std::string& paramString)
{
    (void) paramString; // suppress the 'Unreferenced Formal Parameter' warning.
    // do business logic here
    return std::string();
}

std::future<std::string> TestApi5::funcStringAsync(const std::string& paramString)
{
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            return funcString(paramString);
        }
    );
}

ITestApi5Publisher& TestApi5::_getPublisher() const
{
    return *m_publisher;
}
