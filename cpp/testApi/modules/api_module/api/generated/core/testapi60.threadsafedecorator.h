
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/** 
* @brief The TestApi60ThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the TestApi60 interface.
* @see TestApi60
*
\code{.cpp}
using namespace Cpp::Api;

std::unique_ptr<ITestApi60> testTestApi60 = std::make_unique<TestApi60ThreadSafeDecorator>(std::make_shared<TestApi60>());

// Thread safe access
auto propInt = testTestApi60->getPropInt();
testTestApi60->setPropInt(0);
auto propFloat = testTestApi60->getPropFloat();
testTestApi60->setPropFloat(0.0f);
auto propString = testTestApi60->getPropString();
testTestApi60->setPropString(std::string());
\endcode
*/
class CPP_API_EXPORT TestApi60ThreadSafeDecorator : public ITestApi60
{
public:
    /** 
    * ctor
    * @param impl The TestApi60 object to make thread safe.
    */
    explicit TestApi60ThreadSafeDecorator(std::shared_ptr<ITestApi60> impl);

    /** 
    * Forwards call to TestApi60 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int funcInt(int paramInt) override;
    /** 
    * Forwards call to TestApi60 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int> funcIntAsync(int paramInt) override;

    /** 
    * Forwards call to TestApi60 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat(float paramFloat) override;
    /** 
    * Forwards call to TestApi60 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloatAsync(float paramFloat) override;

    /** 
    * Forwards call to TestApi60 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::string funcString(const std::string& paramString) override;
    /** 
    * Forwards call to TestApi60 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString) override;

    /** Guards and forwards call to TestApi60 implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to TestApi60 implementation. */
    int getPropInt() const override;

    /** Guards and forwards call to TestApi60 implementation. */
    void setPropFloat(float propFloat) override;
    /** Guards and forwards call to TestApi60 implementation. */
    float getPropFloat() const override;

    /** Guards and forwards call to TestApi60 implementation. */
    void setPropString(const std::string& propString) override;
    /** Guards and forwards call to TestApi60 implementation. */
    const std::string& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for TestApi60 changes and signal emission.
    * This call is thread safe.
    * @return The publisher for TestApi60.
    */
    ITestApi60Publisher& _getPublisher() const override;
private:
    /** The TestApi60 object which is guarded */
    std::shared_ptr<ITestApi60> m_impl;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace Api
} // namespace Cpp
