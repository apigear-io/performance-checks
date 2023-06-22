#include "private/olinkwebsockethandler.h"
#include "private/iconnectionstorage.h"
#include "../utilities/logger.h"

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"

#include <iostream>


namespace ApiGear {
namespace PocoImpl {

OLinkWebsocketHandler::OLinkWebsocketHandler(IConnectionStorage& connectionStorage)
    : m_connectionStorage(connectionStorage)
{}

void OLinkWebsocketHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){

    if (request.find("Upgrade") != request.end() &&
        Poco::icompare(request["Upgrade"], "websocket") == 0) {
        AG_LOG_INFO("wss.newConnection()");
        try{
            auto socket = std::make_unique<Poco::Net::WebSocket>(request, response);
            m_connectionStorage.addConnection(std::move(socket));
        }
        catch (Poco::Net::WebSocketException& /*exception*/){
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentLength(0);
            response.send();
        }

    } else {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UPGRADE_REQUIRED);
        response.setContentLength(0);
        response.send();
    }
}

}}   //namespace ApiGear::PocoImpl
