#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"

#include "private/olinkwebsockethandler.h"
#include "private/requesthandlerfactory.h"
#include "private/iconnectionstorage.h"
#include "../utilities/logger.h"

#include <iostream>

namespace ApiGear {
namespace PocoImpl {

RequestHandlerFactory::RequestHandlerFactory(IConnectionStorage& connectionStorage)
: m_connectionStorage(connectionStorage)
{};

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
    AG_LOG_DEBUG("Request from "
        + request.clientAddress().toString() + ": "
        + request.getMethod() + " " + request.getURI() + " " + request.getVersion());

    for (Poco::Net::HTTPServerRequest::ConstIterator it = request.begin(); it != request.end(); ++it)
    {
        AG_LOG_DEBUG(it->first + ": " + it->second);
    }

    // The Poco server implementation takes ownership of the returned HTTPRequestHandler.
    return new OLinkWebsocketHandler(m_connectionStorage);
}


}} //namespace ApiGear::PocoImpl
