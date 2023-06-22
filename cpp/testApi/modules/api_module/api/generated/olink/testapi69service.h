
#pragma once

#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "olink/iobjectsource.h"


namespace ApiGear {
namespace ObjectLink {

class RemoteRegistry;
class IRemoteNode;

}} //namespace ApiGear::ObjectLink

namespace Cpp {
namespace Api {
namespace olink {
/**
* Server side for TestApi69 implements the TestApi69 service.
* It is a source of data for TestApi69 clients.
* Sends and receives data over the network with ObjectLink protocol. 
* see https://objectlinkprotocol.net for Object Link Details
*/
class CPP_API_EXPORT TestApi69Service : public ApiGear::ObjectLink::IObjectSource, public ITestApi69Subscriber
{
public:
    /**
    * ctor
    * @param TestApi69 The service source object, the actual TestApi69 object which is exposed for remote clients with olink.
    * @param registry The global registry that keeps track of the object source services associated with network nodes.
    */
    explicit TestApi69Service(std::shared_ptr<ITestApi69> TestApi69, ApiGear::ObjectLink::RemoteRegistry& registry);
    virtual ~TestApi69Service() override;

    /**
    * The name of the object for which this service is created, object on client side has to have the same name.
    * It serves as an identifier for the source registry, it has to be unique for the pair source object - remote node.
    * Passed in the olink messages as an object identifier.
    */
    std::string olinkObjectName() override;
    /**
    * Applies received method invocation with given arguments on the TestApi69 object.
    * @param name Path of the method to invoke. Contains object name and the method name.
    * @param args Arguments required to invoke a method in json format.
    * @return the result of the invoked method (if applicable) that needs to be sent back to the clients.
    */
    nlohmann::json olinkInvoke(const std::string& methodId, const nlohmann::json& args) override;
    /**
    * Applies received change property request to TestApi69 object.
    * @param name Path the property to change. Contains object name and the property name.
    * @param args Value in json format requested to set for the property.
    */
    void olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) override;
    /**
    * Informs this service source that the link was established.
    * @param name The name of the object for which link was established.
    * @param the initialized link endpoint.
    */
    void olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode *node) override;
    /**
    * Informs this service source that the link was disconnected and cannot be used anymore.
    */
    void olinkUnlinked(const std::string& objectId) override;

    /**
    * Gets the current state of TestApi69 object.
    * @return the set of properties with their current values for the TestApi69 object in json format.
    */
    nlohmann::json olinkCollectProperties() override;
    /**
    * Forwards emitted sigInt through network if the connection is established.
    */
    void onSigInt(int paramInt) override;
    /**
    * Forwards emitted sigFloat through network if the connection is established.
    */
    void onSigFloat(float paramFloat) override;
    /**
    * Forwards emitted sigString through network if the connection is established.
    */
    void onSigString(const std::string& paramString) override;
    /**
    * Forwards propInt change through network if the connection is established.
    */
    void onPropIntChanged(int propInt) override;
    /**
    * Forwards propFloat change through network if the connection is established.
    */
    void onPropFloatChanged(float propFloat) override;
    /**
    * Forwards propString change through network if the connection is established.
    */
    void onPropStringChanged(const std::string& propString) override;

private:
    /**
    * The TestApi69 used for object source.
    */
    std::shared_ptr<ITestApi69> m_TestApi69;
    /**
    * A global registry that keeps track of object sources associated with their network layer nodes.
    */
    ApiGear::ObjectLink::RemoteRegistry& m_registry;
};
} // namespace olink
} // namespace Api
} // namespace Cpp
