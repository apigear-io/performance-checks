

#include "api/generated/core/testapi15.threadsafedecorator.h"

using namespace Cpp::Api;
TestApi15ThreadSafeDecorator::TestApi15ThreadSafeDecorator(std::shared_ptr<ITestApi15> impl)
    : m_impl(impl)
{
}
int TestApi15ThreadSafeDecorator::funcInt(int paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<int> TestApi15ThreadSafeDecorator::funcIntAsync(int paramInt)
{
    return m_impl->funcIntAsync(paramInt);
}
float TestApi15ThreadSafeDecorator::funcFloat(float paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<float> TestApi15ThreadSafeDecorator::funcFloatAsync(float paramFloat)
{
    return m_impl->funcFloatAsync(paramFloat);
}
std::string TestApi15ThreadSafeDecorator::funcString(const std::string& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<std::string> TestApi15ThreadSafeDecorator::funcStringAsync(const std::string& paramString)
{
    return m_impl->funcStringAsync(paramString);
}
void TestApi15ThreadSafeDecorator::setPropInt(int propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

int TestApi15ThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void TestApi15ThreadSafeDecorator::setPropFloat(float propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

float TestApi15ThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void TestApi15ThreadSafeDecorator::setPropString(const std::string& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const std::string& TestApi15ThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

ITestApi15Publisher& TestApi15ThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}