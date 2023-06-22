#pragma once

#include "Poco/Net/HTTPRequestHandler.h"

namespace Poco {
namespace Net {
class HTTPServerRequest;
class HTTPServerResponse;
}} // namespace Poco::Net


namespace ApiGear {
namespace PocoImpl {

class IConnectionStorage;

/**
* Custom implementation of a Poco::Net::HTTPRequestHandler. Provides handling of connection request.
* It's lifetime is controlled by a Poco::Net::HTTPServer. It is created by RequestHandlerFactory by server implementation.
* As soon as the handleRequest() method returns, the request handler object is destroyed.
*/
class OLinkWebsocketHandler : public Poco::Net::HTTPRequestHandler
{
public:
    /**ctor
    @param connectionStorage A storage to which a Poco::Net::Websocket is transfered (with ownership) for accepted connections.
    */
    explicit OLinkWebsocketHandler(IConnectionStorage& connectionStorage);

    /**
    * Handling of the HTTP request connection. 
    * On request accepted creates a websocket used for connection and owned by connectionStorage.
    * @param request A connection request.
    * @param response A response filled depending on acceptation or denial of request.
    */
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
private:
    /** A storage to which a Poco::Net::Websocket is transfered (with ownership) for accepted connections. */
    IConnectionStorage& m_connectionStorage;
};

}}   //namespace ApiGear::PocoImpl
