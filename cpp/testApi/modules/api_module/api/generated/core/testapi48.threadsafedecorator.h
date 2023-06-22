
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/** 
* @brief The TestApi48ThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the TestApi48 interface.
* @see TestApi48
*
\code{.cpp}
using namespace Cpp::Api;

std::unique_ptr<ITestApi48> testTestApi48 = std::make_unique<TestApi48ThreadSafeDecorator>(std::make_shared<TestApi48>());

// Thread safe access
auto propInt = testTestApi48->getPropInt();
testTestApi48->setPropInt(0);
auto propFloat = testTestApi48->getPropFloat();
testTestApi48->setPropFloat(0.0f);
auto propString = testTestApi48->getPropString();
testTestApi48->setPropString(std::string());
\endcode
*/
class CPP_API_EXPORT TestApi48ThreadSafeDecorator : public ITestApi48
{
public:
    /** 
    * ctor
    * @param impl The TestApi48 object to make thread safe.
    */
    explicit TestApi48ThreadSafeDecorator(std::shared_ptr<ITestApi48> impl);

    /** 
    * Forwards call to TestApi48 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int funcInt(int paramInt) override;
    /** 
    * Forwards call to TestApi48 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int> funcIntAsync(int paramInt) override;

    /** 
    * Forwards call to TestApi48 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat(float paramFloat) override;
    /** 
    * Forwards call to TestApi48 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloatAsync(float paramFloat) override;

    /** 
    * Forwards call to TestApi48 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::string funcString(const std::string& paramString) override;
    /** 
    * Forwards call to TestApi48 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString) override;

    /** Guards and forwards call to TestApi48 implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to TestApi48 implementation. */
    int getPropInt() const override;

    /** Guards and forwards call to TestApi48 implementation. */
    void setPropFloat(float propFloat) override;
    /** Guards and forwards call to TestApi48 implementation. */
    float getPropFloat() const override;

    /** Guards and forwards call to TestApi48 implementation. */
    void setPropString(const std::string& propString) override;
    /** Guards and forwards call to TestApi48 implementation. */
    const std::string& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for TestApi48 changes and signal emission.
    * This call is thread safe.
    * @return The publisher for TestApi48.
    */
    ITestApi48Publisher& _getPublisher() const override;
private:
    /** The TestApi48 object which is guarded */
    std::shared_ptr<ITestApi48> m_impl;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace Api
} // namespace Cpp
