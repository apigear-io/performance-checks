#pragma once

#include "api/generated/api/datastructs.api.h"
#include "api/generated/api/testapi20.api.h"
#include "api/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/**
 * The implementation of a TestApi20Publisher.
 * Use this class to store clients of the TestApi20 and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class CPP_API_EXPORT TestApi20Publisher : public ITestApi20Publisher
{
public:
    /**
    * Implementation of ITestApi20Publisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ITestApi20Subscriber& subscriber) override;
    /**
    * Implementation of ITestApi20Publisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ITestApi20Subscriber& subscriber) override;

    /**
    * Implementation of ITestApi20Publisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(TestApi20PropIntPropertyCb callback) override;
    /**
    * Implementation of ITestApi20Publisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of ITestApi20Publisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(TestApi20PropFloatPropertyCb callback) override;
    /**
    * Implementation of ITestApi20Publisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of ITestApi20Publisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(TestApi20PropStringPropertyCb callback) override;
    /**
    * Implementation of ITestApi20Publisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of ITestApi20Publisher::subscribeToSigInt
    */
    long subscribeToSigInt(TestApi20SigIntSignalCb callback) override;
    /**
    * Implementation of ITestApi20Publisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of ITestApi20Publisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(TestApi20SigFloatSignalCb callback) override;
    /**
    * Implementation of ITestApi20Publisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of ITestApi20Publisher::subscribeToSigString
    */
    long subscribeToSigString(TestApi20SigStringSignalCb callback) override;
    /**
    * Implementation of ITestApi20Publisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

    /**
    * Implementation of ITestApi20Publisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
    /**
    * Implementation of ITestApi20Publisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(float propFloat) const override;
    /**
    * Implementation of ITestApi20Publisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::string& propString) const override;
    /**
    * Implementation of ITestApi20Publisher::publishSigInt
    */
    void publishSigInt(int paramInt) const override;
    /**
    * Implementation of ITestApi20Publisher::publishSigFloat
    */
    void publishSigFloat(float paramFloat) const override;
    /**
    * Implementation of ITestApi20Publisher::publishSigString
    */
    void publishSigString(const std::string& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in TestApi20
    std::vector<std::reference_wrapper<ITestApi20Subscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the PropInt change.
    std::atomic<long> m_propIntChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt change.
    std::map<long, TestApi20PropIntPropertyCb> m_propIntCallbacks;
    // Mutex for m_propIntCallbacks
    mutable std::shared_timed_mutex m_propIntCallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat change.
    std::atomic<long> m_propFloatChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat change.
    std::map<long, TestApi20PropFloatPropertyCb> m_propFloatCallbacks;
    // Mutex for m_propFloatCallbacks
    mutable std::shared_timed_mutex m_propFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the PropString change.
    std::atomic<long> m_propStringChangedCallbackNextId {0};
    // Subscribed callbacks for the PropString change.
    std::map<long, TestApi20PropStringPropertyCb> m_propStringCallbacks;
    // Mutex for m_propStringCallbacks
    mutable std::shared_timed_mutex m_propStringCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt emission.
    std::atomic<long> m_sigIntSignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt emission.
    std::map<long, TestApi20SigIntSignalCb > m_sigIntCallbacks;
    // Mutex for m_sigIntSignalCallbackNextId and m_sigIntCallbacks
    mutable std::shared_timed_mutex m_sigIntCallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat emission.
    std::atomic<long> m_sigFloatSignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat emission.
    std::map<long, TestApi20SigFloatSignalCb > m_sigFloatCallbacks;
    // Mutex for m_sigFloatSignalCallbackNextId and m_sigFloatCallbacks
    mutable std::shared_timed_mutex m_sigFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the SigString emission.
    std::atomic<long> m_sigStringSignalCallbackNextId {0};
    // Subscribed callbacks for the SigString emission.
    std::map<long, TestApi20SigStringSignalCb > m_sigStringCallbacks;
    // Mutex for m_sigStringSignalCallbackNextId and m_sigStringCallbacks
    mutable std::shared_timed_mutex m_sigStringCallbacksMutex;
};

} // namespace Api
} // namespace Cpp
