

#include "api/generated/core/testapi10.threadsafedecorator.h"

using namespace Cpp::Api;
TestApi10ThreadSafeDecorator::TestApi10ThreadSafeDecorator(std::shared_ptr<ITestApi10> impl)
    : m_impl(impl)
{
}
int TestApi10ThreadSafeDecorator::funcInt(int paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<int> TestApi10ThreadSafeDecorator::funcIntAsync(int paramInt)
{
    return m_impl->funcIntAsync(paramInt);
}
float TestApi10ThreadSafeDecorator::funcFloat(float paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<float> TestApi10ThreadSafeDecorator::funcFloatAsync(float paramFloat)
{
    return m_impl->funcFloatAsync(paramFloat);
}
std::string TestApi10ThreadSafeDecorator::funcString(const std::string& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<std::string> TestApi10ThreadSafeDecorator::funcStringAsync(const std::string& paramString)
{
    return m_impl->funcStringAsync(paramString);
}
void TestApi10ThreadSafeDecorator::setPropInt(int propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

int TestApi10ThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void TestApi10ThreadSafeDecorator::setPropFloat(float propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

float TestApi10ThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void TestApi10ThreadSafeDecorator::setPropString(const std::string& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const std::string& TestApi10ThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

ITestApi10Publisher& TestApi10ThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}