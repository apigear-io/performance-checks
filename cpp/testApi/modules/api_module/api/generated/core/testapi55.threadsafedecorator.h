
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/** 
* @brief The TestApi55ThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the TestApi55 interface.
* @see TestApi55
*
\code{.cpp}
using namespace Cpp::Api;

std::unique_ptr<ITestApi55> testTestApi55 = std::make_unique<TestApi55ThreadSafeDecorator>(std::make_shared<TestApi55>());

// Thread safe access
auto propInt = testTestApi55->getPropInt();
testTestApi55->setPropInt(0);
auto propFloat = testTestApi55->getPropFloat();
testTestApi55->setPropFloat(0.0f);
auto propString = testTestApi55->getPropString();
testTestApi55->setPropString(std::string());
\endcode
*/
class CPP_API_EXPORT TestApi55ThreadSafeDecorator : public ITestApi55
{
public:
    /** 
    * ctor
    * @param impl The TestApi55 object to make thread safe.
    */
    explicit TestApi55ThreadSafeDecorator(std::shared_ptr<ITestApi55> impl);

    /** 
    * Forwards call to TestApi55 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int funcInt(int paramInt) override;
    /** 
    * Forwards call to TestApi55 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int> funcIntAsync(int paramInt) override;

    /** 
    * Forwards call to TestApi55 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat(float paramFloat) override;
    /** 
    * Forwards call to TestApi55 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloatAsync(float paramFloat) override;

    /** 
    * Forwards call to TestApi55 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::string funcString(const std::string& paramString) override;
    /** 
    * Forwards call to TestApi55 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString) override;

    /** Guards and forwards call to TestApi55 implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to TestApi55 implementation. */
    int getPropInt() const override;

    /** Guards and forwards call to TestApi55 implementation. */
    void setPropFloat(float propFloat) override;
    /** Guards and forwards call to TestApi55 implementation. */
    float getPropFloat() const override;

    /** Guards and forwards call to TestApi55 implementation. */
    void setPropString(const std::string& propString) override;
    /** Guards and forwards call to TestApi55 implementation. */
    const std::string& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for TestApi55 changes and signal emission.
    * This call is thread safe.
    * @return The publisher for TestApi55.
    */
    ITestApi55Publisher& _getPublisher() const override;
private:
    /** The TestApi55 object which is guarded */
    std::shared_ptr<ITestApi55> m_impl;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace Api
} // namespace Cpp
