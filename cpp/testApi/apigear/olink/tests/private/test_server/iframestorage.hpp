#pragma once

#include "tests/private/frame.hpp"

#include <functional>

namespace tests
{
// Helper class for server.
// The frames owner. Stores incoming frames and sends outgoing frames.
// Server implements it to get access to received frames and ability to send frame.
// Used by object managing a socket (TestServerRequestHandler).
class IFrameStorage
{
public:
	virtual ~IFrameStorage() = default;
	// Stores received frame in FrameStorege.
	virtual void storeFrame(const Frame& frame) = 0;
	// Gives ability to send a frame.
	virtual void setRequestSendFunction(std::function<void(Frame)> requestSend) = 0;
};
} //namespace tests