#include "olink/remotenode.h"
#include "api/generated/olink/testapi0service.h"
#include "api/implementation/testapi0.h"
#include "olink/remoteregistry.h"
#include "olink/core/types.h"
#include "apigear/olink/olinkhost.h"
#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>

namespace {
    // Converter used in tests, should be same as one used by node.
    ApiGear::ObjectLink::MessageConverter converter(ApiGear::ObjectLink::MessageFormat::JSON);
}

enum class ServiceStatus
{
    Default,
    LinkedRceived,
    UnlinkedReceived
};

/*
* Class that wraps tested object with additional info used for either test creation purpose:
* the link and unlink info is used to determine when test starts and when it stops.
*/
class TestService : public Cpp::Api::olink::TestApi0Service
{
public:
    TestService(std::shared_ptr<Cpp::Api::ITestApi0> TestApi, ApiGear::ObjectLink::RemoteRegistry& registry)
        :TestApi0Service(TestApi, registry)
    {}

    void olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* node) override
    {
        Cpp::Api::olink::TestApi0Service::olinkLinked(objectId, node);
        m_status = ServiceStatus::LinkedRceived;
    }

    void olinkUnlinked(const std::string& objectId) override
    {
        Cpp::Api::olink::TestApi0Service::olinkUnlinked(objectId);
        m_status = ServiceStatus::UnlinkedReceived;
    }
    ServiceStatus m_status = ServiceStatus::Default;
};

/*
Creates and runs olink server with a stub service, which only handles property changes.
It does not have any implementation for methods and doesn't emit signals.
It finishes work when it receives unlink message for the service it provides.

It does not initiate any action, only responses for change property requests, so test scenario is controlled by client application.
Time measurements starts on link message received and finishes on unlink received.
*/


int main(int argc, char* argv[])
{
    ApiGear::ObjectLink::RemoteRegistry registry;

    auto portNumber = 8000;
    ApiGear::PocoImpl::OLinkHost testHost(registry, [](auto /*level*/, auto /*msg*/){ });
    testHost.listen(portNumber);

    auto source = std::make_shared<Cpp::Api::TestApi0>();
    auto sourceService = std::make_shared<TestService>(source, registry);
    registry.addSource(sourceService);
        
    bool testStarted = false;
    // Will be overwritten with receiving link message
    auto begin = std::chrono::high_resolution_clock::now();

    auto servicesfinished = false;
    do {

        if (!testStarted && sourceService->m_status == ServiceStatus::LinkedRceived)
        {
            testStarted = true;
            begin = std::chrono::high_resolution_clock::now();
        }
        if (sourceService->m_status == ServiceStatus::UnlinkedReceived)
        {
            servicesfinished = true;
        }
            
    } while (!servicesfinished);
    auto end = std::chrono::high_resolution_clock::now();
    Poco::Thread::sleep(200);

    testHost.close();

    auto test_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "server finished work, time measured [ms]" << test_duration.count() << std::endl;
}
