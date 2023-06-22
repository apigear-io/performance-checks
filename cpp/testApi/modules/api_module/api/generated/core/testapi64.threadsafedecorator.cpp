

#include "api/generated/core/testapi64.threadsafedecorator.h"

using namespace Cpp::Api;
TestApi64ThreadSafeDecorator::TestApi64ThreadSafeDecorator(std::shared_ptr<ITestApi64> impl)
    : m_impl(impl)
{
}
int TestApi64ThreadSafeDecorator::funcInt(int paramInt)
{
    return m_impl->funcInt(paramInt);
}

std::future<int> TestApi64ThreadSafeDecorator::funcIntAsync(int paramInt)
{
    return m_impl->funcIntAsync(paramInt);
}
float TestApi64ThreadSafeDecorator::funcFloat(float paramFloat)
{
    return m_impl->funcFloat(paramFloat);
}

std::future<float> TestApi64ThreadSafeDecorator::funcFloatAsync(float paramFloat)
{
    return m_impl->funcFloatAsync(paramFloat);
}
std::string TestApi64ThreadSafeDecorator::funcString(const std::string& paramString)
{
    return m_impl->funcString(paramString);
}

std::future<std::string> TestApi64ThreadSafeDecorator::funcStringAsync(const std::string& paramString)
{
    return m_impl->funcStringAsync(paramString);
}
void TestApi64ThreadSafeDecorator::setPropInt(int propInt)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    m_impl->setPropInt(propInt);
}

int TestApi64ThreadSafeDecorator::getPropInt() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propIntMutex);
    return m_impl->getPropInt();
}
void TestApi64ThreadSafeDecorator::setPropFloat(float propFloat)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    m_impl->setPropFloat(propFloat);
}

float TestApi64ThreadSafeDecorator::getPropFloat() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propFloatMutex);
    return m_impl->getPropFloat();
}
void TestApi64ThreadSafeDecorator::setPropString(const std::string& propString)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    m_impl->setPropString(propString);
}

const std::string& TestApi64ThreadSafeDecorator::getPropString() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_propStringMutex);
    return m_impl->getPropString();
}

ITestApi64Publisher& TestApi64ThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}