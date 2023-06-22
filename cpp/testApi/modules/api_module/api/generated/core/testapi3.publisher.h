#pragma once

#include "api/generated/api/datastructs.api.h"
#include "api/generated/api/testapi3.api.h"
#include "api/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Cpp {
namespace Api {

/**
 * The implementation of a TestApi3Publisher.
 * Use this class to store clients of the TestApi3 and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class CPP_API_EXPORT TestApi3Publisher : public ITestApi3Publisher
{
public:
    /**
    * Implementation of ITestApi3Publisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(ITestApi3Subscriber& subscriber) override;
    /**
    * Implementation of ITestApi3Publisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(ITestApi3Subscriber& subscriber) override;

    /**
    * Implementation of ITestApi3Publisher::subscribeToPropIntChanged
    */
    long subscribeToPropIntChanged(TestApi3PropIntPropertyCb callback) override;
    /**
    * Implementation of ITestApi3Publisher::subscribeToPropIntChanged
    */
    void unsubscribeFromPropIntChanged(long handleId) override;

    /**
    * Implementation of ITestApi3Publisher::subscribeToPropFloatChanged
    */
    long subscribeToPropFloatChanged(TestApi3PropFloatPropertyCb callback) override;
    /**
    * Implementation of ITestApi3Publisher::subscribeToPropFloatChanged
    */
    void unsubscribeFromPropFloatChanged(long handleId) override;

    /**
    * Implementation of ITestApi3Publisher::subscribeToPropStringChanged
    */
    long subscribeToPropStringChanged(TestApi3PropStringPropertyCb callback) override;
    /**
    * Implementation of ITestApi3Publisher::subscribeToPropStringChanged
    */
    void unsubscribeFromPropStringChanged(long handleId) override;

    /**
    * Implementation of ITestApi3Publisher::subscribeToSigInt
    */
    long subscribeToSigInt(TestApi3SigIntSignalCb callback) override;
    /**
    * Implementation of ITestApi3Publisher::unsubscribeFromSigInt
    */
    void unsubscribeFromSigInt(long handleId) override;

    /**
    * Implementation of ITestApi3Publisher::subscribeToSigFloat
    */
    long subscribeToSigFloat(TestApi3SigFloatSignalCb callback) override;
    /**
    * Implementation of ITestApi3Publisher::unsubscribeFromSigFloat
    */
    void unsubscribeFromSigFloat(long handleId) override;

    /**
    * Implementation of ITestApi3Publisher::subscribeToSigString
    */
    long subscribeToSigString(TestApi3SigStringSignalCb callback) override;
    /**
    * Implementation of ITestApi3Publisher::unsubscribeFromSigString
    */
    void unsubscribeFromSigString(long handleId) override;

    /**
    * Implementation of ITestApi3Publisher::publishPropIntChanged
    */
    void publishPropIntChanged(int propInt) const override;
    /**
    * Implementation of ITestApi3Publisher::publishPropFloatChanged
    */
    void publishPropFloatChanged(float propFloat) const override;
    /**
    * Implementation of ITestApi3Publisher::publishPropStringChanged
    */
    void publishPropStringChanged(const std::string& propString) const override;
    /**
    * Implementation of ITestApi3Publisher::publishSigInt
    */
    void publishSigInt(int paramInt) const override;
    /**
    * Implementation of ITestApi3Publisher::publishSigFloat
    */
    void publishSigFloat(float paramFloat) const override;
    /**
    * Implementation of ITestApi3Publisher::publishSigString
    */
    void publishSigString(const std::string& paramString) const override;
private:
    // Subscribers informed about any property change or signal emitted in TestApi3
    std::vector<std::reference_wrapper<ITestApi3Subscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the PropInt change.
    std::atomic<long> m_propIntChangedCallbackNextId {0};
    // Subscribed callbacks for the PropInt change.
    std::map<long, TestApi3PropIntPropertyCb> m_propIntCallbacks;
    // Mutex for m_propIntCallbacks
    mutable std::shared_timed_mutex m_propIntCallbacksMutex;
    // Next free unique identifier to subscribe for the PropFloat change.
    std::atomic<long> m_propFloatChangedCallbackNextId {0};
    // Subscribed callbacks for the PropFloat change.
    std::map<long, TestApi3PropFloatPropertyCb> m_propFloatCallbacks;
    // Mutex for m_propFloatCallbacks
    mutable std::shared_timed_mutex m_propFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the PropString change.
    std::atomic<long> m_propStringChangedCallbackNextId {0};
    // Subscribed callbacks for the PropString change.
    std::map<long, TestApi3PropStringPropertyCb> m_propStringCallbacks;
    // Mutex for m_propStringCallbacks
    mutable std::shared_timed_mutex m_propStringCallbacksMutex;
    // Next free unique identifier to subscribe for the SigInt emission.
    std::atomic<long> m_sigIntSignalCallbackNextId {0};
    // Subscribed callbacks for the SigInt emission.
    std::map<long, TestApi3SigIntSignalCb > m_sigIntCallbacks;
    // Mutex for m_sigIntSignalCallbackNextId and m_sigIntCallbacks
    mutable std::shared_timed_mutex m_sigIntCallbacksMutex;
    // Next free unique identifier to subscribe for the SigFloat emission.
    std::atomic<long> m_sigFloatSignalCallbackNextId {0};
    // Subscribed callbacks for the SigFloat emission.
    std::map<long, TestApi3SigFloatSignalCb > m_sigFloatCallbacks;
    // Mutex for m_sigFloatSignalCallbackNextId and m_sigFloatCallbacks
    mutable std::shared_timed_mutex m_sigFloatCallbacksMutex;
    // Next free unique identifier to subscribe for the SigString emission.
    std::atomic<long> m_sigStringSignalCallbackNextId {0};
    // Subscribed callbacks for the SigString emission.
    std::map<long, TestApi3SigStringSignalCb > m_sigStringCallbacks;
    // Mutex for m_sigStringSignalCallbackNextId and m_sigStringCallbacks
    mutable std::shared_timed_mutex m_sigStringCallbacksMutex;
};

} // namespace Api
} // namespace Cpp
