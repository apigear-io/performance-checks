#pragma once

#include "api/generated/api/datastructs.api.h"
#include "api/generated/api/testapi57.api.h"
#include "api/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/**
 * The implementation of a TestApi57Publisher.
 * Use this class to store clients of the TestApi57 and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class CPP_API_EXPORT TestApi57Publisher : public ITestApi57Publisher
{
public:
    /**
    * Implementation of ITestApi57Publisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ITestApi57Subscriber& subscriber) override;
    /**
    * Implementation of ITestApi57Publisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ITestApi57Subscriber& subscriber) override;

    /**
    * Implementation of ITestApi57Publisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(TestApi57PropIntPropertyCb callback) override;
    /**
    * Implementation of ITestApi57Publisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of ITestApi57Publisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(TestApi57PropFloatPropertyCb callback) override;
    /**
    * Implementation of ITestApi57Publisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of ITestApi57Publisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(TestApi57PropStringPropertyCb callback) override;
    /**
    * Implementation of ITestApi57Publisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of ITestApi57Publisher::subscribeToSigInt
    */
    long subscribeToSigInt(TestApi57SigIntSignalCb callback) override;
    /**
    * Implementation of ITestApi57Publisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of ITestApi57Publisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(TestApi57SigFloatSignalCb callback) override;
    /**
    * Implementation of ITestApi57Publisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of ITestApi57Publisher::subscribeToSigString
    */
    long subscribeToSigString(TestApi57SigStringSignalCb callback) override;
    /**
    * Implementation of ITestApi57Publisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

    /**
    * Implementation of ITestApi57Publisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
    /**
    * Implementation of ITestApi57Publisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(float propFloat) const override;
    /**
    * Implementation of ITestApi57Publisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::string& propString) const override;
    /**
    * Implementation of ITestApi57Publisher::publishSigInt
    */
    void publishSigInt(int paramInt) const override;
    /**
    * Implementation of ITestApi57Publisher::publishSigFloat
    */
    void publishSigFloat(float paramFloat) const override;
    /**
    * Implementation of ITestApi57Publisher::publishSigString
    */
    void publishSigString(const std::string& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in TestApi57
    std::vector<std::reference_wrapper<ITestApi57Subscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the PropInt change.
    std::atomic<long> m_propIntChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt change.
    std::map<long, TestApi57PropIntPropertyCb> m_propIntCallbacks;
    // Mutex for m_propIntCallbacks
    mutable std::shared_timed_mutex m_propIntCallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat change.
    std::atomic<long> m_propFloatChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat change.
    std::map<long, TestApi57PropFloatPropertyCb> m_propFloatCallbacks;
    // Mutex for m_propFloatCallbacks
    mutable std::shared_timed_mutex m_propFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the PropString change.
    std::atomic<long> m_propStringChangedCallbackNextId {0};
    // Subscribed callbacks for the PropString change.
    std::map<long, TestApi57PropStringPropertyCb> m_propStringCallbacks;
    // Mutex for m_propStringCallbacks
    mutable std::shared_timed_mutex m_propStringCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt emission.
    std::atomic<long> m_sigIntSignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt emission.
    std::map<long, TestApi57SigIntSignalCb > m_sigIntCallbacks;
    // Mutex for m_sigIntSignalCallbackNextId and m_sigIntCallbacks
    mutable std::shared_timed_mutex m_sigIntCallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat emission.
    std::atomic<long> m_sigFloatSignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat emission.
    std::map<long, TestApi57SigFloatSignalCb > m_sigFloatCallbacks;
    // Mutex for m_sigFloatSignalCallbackNextId and m_sigFloatCallbacks
    mutable std::shared_timed_mutex m_sigFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the SigString emission.
    std::atomic<long> m_sigStringSignalCallbackNextId {0};
    // Subscribed callbacks for the SigString emission.
    std::map<long, TestApi57SigStringSignalCb > m_sigStringCallbacks;
    // Mutex for m_sigStringSignalCallbackNextId and m_sigStringCallbacks
    mutable std::shared_timed_mutex m_sigStringCallbacksMutex;
};

} // namespace Api
} // namespace Cpp
