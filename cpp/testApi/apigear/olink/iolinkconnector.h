#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define APIGEAR_OLINK_EXPORT __attribute__ ((dllexport))
#else
#define APIGEAR_OLINK_EXPORT __declspec(dllexport)
#endif
#else
#if __GNUC__ >= 4
#define APIGEAR_OLINK_EXPORT __attribute__ ((visibility ("default")))
#else
#define APIGEAR_OLINK_EXPORT
#endif
#endif

#include <string>
#include <memory>

namespace ApiGear {
// Forward declaration for IObjectSink
namespace ObjectLink {
class IObjectSink;
}

namespace PocoImpl {

/**
* A helper class for handling setting up and tear down the olink side for sink.
* The implementation should provide a ClientNode and take care of remote linking and unlinking
* depending on the connection state (if any).
*/
class APIGEAR_OLINK_EXPORT IOlinkConnector
{
public:
    virtual ~IOlinkConnector() = default;

    /** Use this function to setup linkage with the service object.
    * Connect your sink with protocol handling node, and request linking with service object.
    * After successful linking the IObjectSink will receive confirmation from service with olinkOnInit handler call.
    * @param object An olink sink object which will be associated with protocol handling node and for which linking with service object will be requested.
    */
    virtual void connectAndLinkObject(std::shared_ptr<ApiGear::ObjectLink::IObjectSink> object) = 0;
    /**Use this function to disconnect your sink from protocol handling node, and request unlinking with service object.
    * @param object An objectId no longer interested of using the service.
    */
    virtual void disconnectAndUnlink(const std::string& objectId) = 0;
};
}} //Apigear::PocoImpl
