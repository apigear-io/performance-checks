

#include "api/generated/core/testapi42.threadsafedecorator.h"

using namespace Cpp::Api;
TestApi42ThreadSafeDecorator::TestApi42ThreadSafeDecorator(std::shared_ptr<ITestApi42> impl)
    : m_impl(impl)
{
}
int TestApi42ThreadSafeDecorator::funcInt(int paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<int> TestApi42ThreadSafeDecorator::funcIntAsync(int paramInt)
{
    return m_impl->funcIntAsync(paramInt);
}
float TestApi42ThreadSafeDecorator::funcFloat(float paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<float> TestApi42ThreadSafeDecorator::funcFloatAsync(float paramFloat)
{
    return m_impl->funcFloatAsync(paramFloat);
}
std::string TestApi42ThreadSafeDecorator::funcString(const std::string& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<std::string> TestApi42ThreadSafeDecorator::funcStringAsync(const std::string& paramString)
{
    return m_impl->funcStringAsync(paramString);
}
void TestApi42ThreadSafeDecorator::setPropInt(int propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

int TestApi42ThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void TestApi42ThreadSafeDecorator::setPropFloat(float propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

float TestApi42ThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void TestApi42ThreadSafeDecorator::setPropString(const std::string& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const std::string& TestApi42ThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

ITestApi42Publisher& TestApi42ThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}