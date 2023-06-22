#pragma once

#include <memory>

namespace Poco {
namespace Net {
class WebSocket;
}
} //namespace Poco::Net

namespace ApiGear{
namespace PocoImpl{

class OLinkRemote;

/**
* An Interface for helper class that stores connections for OlinkHost.
* Used for objects that are related to connection lifetime.
*/
class IConnectionStorage
{
public:
virtual ~IConnectionStorage() = default;
/**
* Notification that one of connections was closed from client side and is in closed state, allows the storage to search for it and remove.
*/
virtual void notifyConnectionClosed() = 0;
/**
* Add new server connection requested by a client.
* @param connectionSocket. A socket to be use by new connection.
*/
virtual void addConnection(std::unique_ptr<Poco::Net::WebSocket> connectionSocket) = 0;
};

}}  //namespace ApiGear::PocoImpl
