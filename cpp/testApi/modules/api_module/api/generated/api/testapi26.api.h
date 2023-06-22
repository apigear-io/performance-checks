#pragma once

#include <future>
#include "api/generated/api/common.h"
#include "api/generated/api/datastructs.api.h"

namespace Cpp {
namespace Api {

class ITestApi26Subscriber;
class ITestApi26Publisher;

/**
*
* ITestApi26 provides an interface for
 *  - methods defined for your TestApi26 
 *  - property setters and getters for defined properties
 * The ITestApi26 also provides an interface to access a publisher ITestApi26Publisher, a class used by ITestApi26Subscriber clients.
 * The implementation should notify the publisher ITestApi26Publisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also ITestApi26Subscriber, ITestApi26Publisher
 * and the example implementation TestApi26  or the
 */
class CPP_API_EXPORT ITestApi26
{
public:
    virtual ~ITestApi26() = default;


    virtual int funcInt(int paramInt) = 0;
    /**
    * Asynchronous version of funcInt(int paramInt)
    * @return Promise of type int which is set once the function has completed
    */
    virtual std::future<int> funcIntAsync(int paramInt) = 0;


    virtual float funcFloat(float paramFloat) = 0;
    /**
    * Asynchronous version of funcFloat(float paramFloat)
    * @return Promise of type float which is set once the function has completed
    */
    virtual std::future<float> funcFloatAsync(float paramFloat) = 0;


    virtual std::string funcString(const std::string& paramString) = 0;
    /**
    * Asynchronous version of funcString(const std::string& paramString)
    * @return Promise of type std::string which is set once the function has completed
    */
    virtual std::future<std::string> funcStringAsync(const std::string& paramString) = 0;

    /**
    * Sets the value of the propInt property.
    */
    virtual void setPropInt(int propInt) = 0;
    /**
    * Gets the value of the propInt property.
    */
    virtual int getPropInt() const = 0;

    /**
    * Sets the value of the propFloat property.
    */
    virtual void setPropFloat(float propFloat) = 0;
    /**
    * Gets the value of the propFloat property.
    */
    virtual float getPropFloat() const = 0;

    /**
    * Sets the value of the propString property.
    */
    virtual void setPropString(const std::string& propString) = 0;
    /**
    * Gets the value of the propString property.
    */
    virtual const std::string& getPropString() const = 0;

    /**
    * Access to a publisher, use it to subscribe for TestApi26 changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for TestApi26.
    */
    virtual ITestApi26Publisher& _getPublisher() const = 0;
};


/**
 * The ITestApi26Subscriber contains functions to allow informing about signals or property changes of the ITestApi26 implementation.
 * The implementation for ITestApi26 should provide mechanism for subscription of the ITestApi26Subscriber clients.
 * See ITestApi26Publisher, which provides facilitation for this purpose.
 * The implementation for ITestApi26 should call the ITestApi26Subscriber interface functions on either signal emit or property change.
 * You can use ITestApi26Subscriber class to implement clients of the ITestApi26 or the network adapter - see Olink Server and Client example.
 */
class CPP_API_EXPORT ITestApi26Subscriber
{
public:
    virtual ~ITestApi26Subscriber() = default;
    /**
    * Called by the ITestApi26Publisher when the TestApi26 emits sigInt, if subscribed for the sigInt.
    * @param paramInt 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigInt(int paramInt) = 0;
    /**
    * Called by the ITestApi26Publisher when the TestApi26 emits sigFloat, if subscribed for the sigFloat.
    * @param paramFloat 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigFloat(float paramFloat) = 0;
    /**
    * Called by the ITestApi26Publisher when the TestApi26 emits sigString, if subscribed for the sigString.
    * @param paramString 
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSigString(const std::string& paramString) = 0;
    /**
    * Called by the ITestApi26Publisher when propInt value has changed if subscribed for the propInt change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropIntChanged(int propInt) = 0;
    /**
    * Called by the ITestApi26Publisher when propFloat value has changed if subscribed for the propFloat change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropFloatChanged(float propFloat) = 0;
    /**
    * Called by the ITestApi26Publisher when propString value has changed if subscribed for the propString change.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onPropStringChanged(const std::string& propString) = 0;
};

/** Callback for changes of propInt */
using TestApi26PropIntPropertyCb = std::function<void(int propInt)>;
/** Callback for changes of propFloat */
using TestApi26PropFloatPropertyCb = std::function<void(float propFloat)>;
/** Callback for changes of propString */
using TestApi26PropStringPropertyCb = std::function<void(const std::string& propString)>;
/** Callback for sigInt signal triggers */
using TestApi26SigIntSignalCb = std::function<void(int paramInt)> ;
/** Callback for sigFloat signal triggers */
using TestApi26SigFloatSignalCb = std::function<void(float paramFloat)> ;
/** Callback for sigString signal triggers */
using TestApi26SigStringSignalCb = std::function<void(const std::string& paramString)> ;


/**
 * The ITestApi26Publisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your ITestApi26 implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a ITestApi26Subscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IITestApi26 on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class CPP_API_EXPORT ITestApi26Publisher
{
public:
    virtual ~ITestApi26Publisher() = default;

    /**
    * Use this function to subscribe for any change of the TestApi26.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param ITestApi26Subscriber which is subscribed in this function to any change of the TestApi26.
    */
    virtual void subscribeToAllChanges(ITestApi26Subscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the TestApi26.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param ITestApi26Subscriber which subscription for any change of the TestApi26 is removed.
    */
    virtual void unsubscribeFromAllChanges(ITestApi26Subscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for propInt value changes.
    * If your subscriber uses subscription with ITestApi26Subscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param TestApi26PropIntPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropIntChanged(TestApi26PropIntPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propInt property changes.
    * If your subscriber uses subscription with ITestApi26Subscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropIntChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propFloat value changes.
    * If your subscriber uses subscription with ITestApi26Subscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param TestApi26PropFloatPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropFloatChanged(TestApi26PropFloatPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propFloat property changes.
    * If your subscriber uses subscription with ITestApi26Subscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropFloatChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for propString value changes.
    * If your subscriber uses subscription with ITestApi26Subscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param TestApi26PropStringPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToPropStringChanged(TestApi26PropStringPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from propString property changes.
    * If your subscriber uses subscription with ITestApi26Subscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromPropStringChanged(long handleId) = 0;

    /**
    * Use this function to subscribe for sigInt signal changes.
    * @param TestApi26SigIntSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigInt(TestApi26SigIntSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigInt signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigInt(long handleId) = 0;

    /**
    * Use this function to subscribe for sigFloat signal changes.
    * @param TestApi26SigFloatSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigFloat(TestApi26SigFloatSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigFloat signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigFloat(long handleId) = 0;

    /**
    * Use this function to subscribe for sigString signal changes.
    * @param TestApi26SigStringSignalCb callback that will be executed on each signal emission.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSigString(TestApi26SigStringSignalCb callback) = 0;
    /**
    * Use this function to unsubscribe from sigString signal changes.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSigString(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the TestApi26 implementation when property propInt changes.
    * @param The new value of propInt.
    */
    virtual void publishPropIntChanged(int propInt) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the TestApi26 implementation when property propFloat changes.
    * @param The new value of propFloat.
    */
    virtual void publishPropFloatChanged(float propFloat) const = 0;
    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the TestApi26 implementation when property propString changes.
    * @param The new value of propString.
    */
    virtual void publishPropStringChanged(const std::string& propString) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the TestApi26 implementation when sigInt is emitted.
    * @param paramInt 
    */
    virtual void publishSigInt(int paramInt) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the TestApi26 implementation when sigFloat is emitted.
    * @param paramFloat 
    */
    virtual void publishSigFloat(float paramFloat) const = 0;
    /**
    * Publishes the emitted signal to all subscribed clients.
    * Needs to be invoked by the TestApi26 implementation when sigString is emitted.
    * @param paramString 
    */
    virtual void publishSigString(const std::string& paramString) const = 0;
};


} // namespace Api
} // namespace Cpp
