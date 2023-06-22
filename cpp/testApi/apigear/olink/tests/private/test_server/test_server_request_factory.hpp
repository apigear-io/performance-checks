#pragma once

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"

#include "tests/private/test_server/iframestorage.hpp"
#include "tests/private/test_server/test_server_request_handler.hpp"

namespace tests
{
// Test server request handler factory.
// On new connection request provides a handler that uses the IFrameStorage implemented by TestServer.
class TestServerRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
	TestServerRequestHandlerFactory(IFrameStorage& frameStorage)
		:m_frameStorage(frameStorage)
	{
	}

	// The POCO will takes ownership of request handler.
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override
	{
		return new TestServerRequestHandler(m_frameStorage);
	}
	IFrameStorage& m_frameStorage;
};
}// namespace tests
