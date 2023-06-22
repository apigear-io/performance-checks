
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/** 
* @brief The TestApi9ThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the TestApi9 interface.
* @see TestApi9
*
\code{.cpp}
using namespace Cpp::Api;

std::unique_ptr<ITestApi9> testTestApi9 = std::make_unique<TestApi9ThreadSafeDecorator>(std::make_shared<TestApi9>());

// Thread safe access
auto propInt = testTestApi9->getPropInt();
testTestApi9->setPropInt(0);
auto propFloat = testTestApi9->getPropFloat();
testTestApi9->setPropFloat(0.0f);
auto propString = testTestApi9->getPropString();
testTestApi9->setPropString(std::string());
\endcode
*/
class CPP_API_EXPORT TestApi9ThreadSafeDecorator : public ITestApi9
{
public:
    /** 
    * ctor
    * @param impl The TestApi9 object to make thread safe.
    */
    explicit TestApi9ThreadSafeDecorator(std::shared_ptr<ITestApi9> impl);

    /** 
    * Forwards call to TestApi9 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    int funcInt(int paramInt) override;
    /** 
    * Forwards call to TestApi9 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<int> funcIntAsync(int paramInt) override;

    /** 
    * Forwards call to TestApi9 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    float funcFloat(float paramFloat) override;
    /** 
    * Forwards call to TestApi9 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<float> funcFloatAsync(float paramFloat) override;

    /** 
    * Forwards call to TestApi9 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::string funcString(const std::string& paramString) override;
    /** 
    * Forwards call to TestApi9 implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<std::string> funcStringAsync(const std::string& paramString) override;

    /** Guards and forwards call to TestApi9 implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to TestApi9 implementation. */
    int getPropInt() const override;

    /** Guards and forwards call to TestApi9 implementation. */
    void setPropFloat(float propFloat) override;
    /** Guards and forwards call to TestApi9 implementation. */
    float getPropFloat() const override;

    /** Guards and forwards call to TestApi9 implementation. */
    void setPropString(const std::string& propString) override;
    /** Guards and forwards call to TestApi9 implementation. */
    const std::string& getPropString() const override;

    /**
    * Access to a publisher, use it to subscribe for TestApi9 changes and signal emission.
    * This call is thread safe.
    * @return The publisher for TestApi9.
    */
    ITestApi9Publisher& _getPublisher() const override;
private:
    /** The TestApi9 object which is guarded */
    std::shared_ptr<ITestApi9> m_impl;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
    // Mutex for propFloat property
    mutable std::shared_timed_mutex m_propFloatMutex;
    // Mutex for propString property
    mutable std::shared_timed_mutex m_propStringMutex;
};
} // namespace Api
} // namespace Cpp
