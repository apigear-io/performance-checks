#pragma once

#include "private/apigear_olink.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// HTTPServerRequest forward declaration
namespace Poco {
namespace Net {
class HTTPServerRequest;
}} //namespace Poco::Net

namespace ApiGear {
namespace PocoImpl {

// IConnectionStorage forward declaration
class IConnectionStorage;

/**
* Helper class for implementing a Poco server.
* Poco implementation allows providing a request factory implementation
* which produces custom request handlers for a connection request.
* See https://docs.pocoproject.org/current/Poco.Net.HTTPRequestHandlerFactory.html for more information
* See OLinkWebsocketHandler for a custom implementation of a handler.
*/
class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    /**
    * ctor
    * @param connectionStorage A storage to which a Poco::Net::Websocket is transfered (with ownership) for accepted connections.
    */
    RequestHandlerFactory(IConnectionStorage& connectionStorage);

    /**
    * Creates a new request handler for the given HTTP request, called by Poco::Net::Server.
    * @param request A server request for a new connection.
    * @return A custom request handler. The Poco::Net::Server takes ownership of the created request handler.
    */
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
private:
    /**A storage to which a Poco::Net::Websocket is transfered (with ownership) for accepted connections.*/
    IConnectionStorage& m_connectionStorage;
};

}} //namespace ApiGear::PocoImpl
