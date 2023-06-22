
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/** 
* @brief The TestApi13ThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the TestApi13 interface.
* @see TestApi13
*
\code{.cpp}
using namespace Cpp::Api;

std::unique_ptr<ITestApi13> testTestApi13 = std::make_unique<TestApi13ThreadSafeDecorator>(std::make_shared<TestApi13>());

// Thread safe access
auto propInt = testTestApi13->getPropInt();
testTestApi13->setPropInt(0);
auto propFloat = testTestApi13->getPropFloat();
testTestApi13->setPropFloat(0.0f);
auto propString = testTestApi13->getPropString();
testTestApi13->setPropString(std::string());
\endcode
*/
class CPP_API_EXPORT TestApi13ThreadSafeDecorator : public ITestApi13
{
public:
    /** 
    * ctor
    * @param impl The TestApi13 object to make thread safe.
    */
    explicit TestApi13ThreadSafeDecorator(std::shared_ptr<ITestApi13> impl);

    /** 
    * Forwards call to TestApi13 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int funcInt(int paramInt) override;
    /** 
    * Forwards call to TestApi13 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int> funcIntAsync(int paramInt) override;

    /** 
    * Forwards call to TestApi13 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat(float paramFloat) override;
    /** 
    * Forwards call to TestApi13 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloatAsync(float paramFloat) override;

    /** 
    * Forwards call to TestApi13 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::string funcString(const std::string& paramString) override;
    /** 
    * Forwards call to TestApi13 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString) override;

    /** Guards and forwards call to TestApi13 implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to TestApi13 implementation. */
    int getPropInt() const override;

    /** Guards and forwards call to TestApi13 implementation. */
    void setPropFloat(float propFloat) override;
    /** Guards and forwards call to TestApi13 implementation. */
    float getPropFloat() const override;

    /** Guards and forwards call to TestApi13 implementation. */
    void setPropString(const std::string& propString) override;
    /** Guards and forwards call to TestApi13 implementation. */
    const std::string& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for TestApi13 changes and signal emission.
    * This call is thread safe.
    * @return The publisher for TestApi13.
    */
    ITestApi13Publisher& _getPublisher() const override;
private:
    /** The TestApi13 object which is guarded */
    std::shared_ptr<ITestApi13> m_impl;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace Api
} // namespace Cpp
