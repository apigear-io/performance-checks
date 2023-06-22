
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/** 
* @brief The TestApi36ThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the TestApi36 interface.
* @see TestApi36
*
\code{.cpp}
using namespace Cpp::Api;

std::unique_ptr<ITestApi36> testTestApi36 = std::make_unique<TestApi36ThreadSafeDecorator>(std::make_shared<TestApi36>());

// Thread safe access
auto propInt = testTestApi36->getPropInt();
testTestApi36->setPropInt(0);
auto propFloat = testTestApi36->getPropFloat();
testTestApi36->setPropFloat(0.0f);
auto propString = testTestApi36->getPropString();
testTestApi36->setPropString(std::string());
\endcode
*/
class CPP_API_EXPORT TestApi36ThreadSafeDecorator : public ITestApi36
{
public:
    /** 
    * ctor
    * @param impl The TestApi36 object to make thread safe.
    */
    explicit TestApi36ThreadSafeDecorator(std::shared_ptr<ITestApi36> impl);

    /** 
    * Forwards call to TestApi36 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int funcInt(int paramInt) override;
    /** 
    * Forwards call to TestApi36 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int> funcIntAsync(int paramInt) override;

    /** 
    * Forwards call to TestApi36 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat(float paramFloat) override;
    /** 
    * Forwards call to TestApi36 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloatAsync(float paramFloat) override;

    /** 
    * Forwards call to TestApi36 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::string funcString(const std::string& paramString) override;
    /** 
    * Forwards call to TestApi36 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString) override;

    /** Guards and forwards call to TestApi36 implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to TestApi36 implementation. */
    int getPropInt() const override;

    /** Guards and forwards call to TestApi36 implementation. */
    void setPropFloat(float propFloat) override;
    /** Guards and forwards call to TestApi36 implementation. */
    float getPropFloat() const override;

    /** Guards and forwards call to TestApi36 implementation. */
    void setPropString(const std::string& propString) override;
    /** Guards and forwards call to TestApi36 implementation. */
    const std::string& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for TestApi36 changes and signal emission.
    * This call is thread safe.
    * @return The publisher for TestApi36.
    */
    ITestApi36Publisher& _getPublisher() const override;
private:
    /** The TestApi36 object which is guarded */
    std::shared_ptr<ITestApi36> m_impl;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace Api
} // namespace Cpp
