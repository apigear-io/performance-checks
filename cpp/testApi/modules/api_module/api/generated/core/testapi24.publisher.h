#pragma once

#include "api/generated/api/datastructs.api.h"
#include "api/generated/api/testapi24.api.h"
#include "api/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/**
 * The implementation of a TestApi24Publisher.
 * Use this class to store clients of the TestApi24 and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class CPP_API_EXPORT TestApi24Publisher : public ITestApi24Publisher
{
public:
    /**
    * Implementation of ITestApi24Publisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ITestApi24Subscriber& subscriber) override;
    /**
    * Implementation of ITestApi24Publisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ITestApi24Subscriber& subscriber) override;

    /**
    * Implementation of ITestApi24Publisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(TestApi24PropIntPropertyCb callback) override;
    /**
    * Implementation of ITestApi24Publisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of ITestApi24Publisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(TestApi24PropFloatPropertyCb callback) override;
    /**
    * Implementation of ITestApi24Publisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of ITestApi24Publisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(TestApi24PropStringPropertyCb callback) override;
    /**
    * Implementation of ITestApi24Publisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of ITestApi24Publisher::subscribeToSigInt
    */
    long subscribeToSigInt(TestApi24SigIntSignalCb callback) override;
    /**
    * Implementation of ITestApi24Publisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of ITestApi24Publisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(TestApi24SigFloatSignalCb callback) override;
    /**
    * Implementation of ITestApi24Publisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of ITestApi24Publisher::subscribeToSigString
    */
    long subscribeToSigString(TestApi24SigStringSignalCb callback) override;
    /**
    * Implementation of ITestApi24Publisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

    /**
    * Implementation of ITestApi24Publisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
    /**
    * Implementation of ITestApi24Publisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(float propFloat) const override;
    /**
    * Implementation of ITestApi24Publisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::string& propString) const override;
    /**
    * Implementation of ITestApi24Publisher::publishSigInt
    */
    void publishSigInt(int paramInt) const override;
    /**
    * Implementation of ITestApi24Publisher::publishSigFloat
    */
    void publishSigFloat(float paramFloat) const override;
    /**
    * Implementation of ITestApi24Publisher::publishSigString
    */
    void publishSigString(const std::string& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in TestApi24
    std::vector<std::reference_wrapper<ITestApi24Subscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the PropInt change.
    std::atomic<long> m_propIntChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt change.
    std::map<long, TestApi24PropIntPropertyCb> m_propIntCallbacks;
    // Mutex for m_propIntCallbacks
    mutable std::shared_timed_mutex m_propIntCallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat change.
    std::atomic<long> m_propFloatChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat change.
    std::map<long, TestApi24PropFloatPropertyCb> m_propFloatCallbacks;
    // Mutex for m_propFloatCallbacks
    mutable std::shared_timed_mutex m_propFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the PropString change.
    std::atomic<long> m_propStringChangedCallbackNextId {0};
    // Subscribed callbacks for the PropString change.
    std::map<long, TestApi24PropStringPropertyCb> m_propStringCallbacks;
    // Mutex for m_propStringCallbacks
    mutable std::shared_timed_mutex m_propStringCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt emission.
    std::atomic<long> m_sigIntSignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt emission.
    std::map<long, TestApi24SigIntSignalCb > m_sigIntCallbacks;
    // Mutex for m_sigIntSignalCallbackNextId and m_sigIntCallbacks
    mutable std::shared_timed_mutex m_sigIntCallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat emission.
    std::atomic<long> m_sigFloatSignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat emission.
    std::map<long, TestApi24SigFloatSignalCb > m_sigFloatCallbacks;
    // Mutex for m_sigFloatSignalCallbackNextId and m_sigFloatCallbacks
    mutable std::shared_timed_mutex m_sigFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the SigString emission.
    std::atomic<long> m_sigStringSignalCallbackNextId {0};
    // Subscribed callbacks for the SigString emission.
    std::map<long, TestApi24SigStringSignalCb > m_sigStringCallbacks;
    // Mutex for m_sigStringSignalCallbackNextId and m_sigStringCallbacks
    mutable std::shared_timed_mutex m_sigStringCallbacksMutex;
};

} // namespace Api
} // namespace Cpp
