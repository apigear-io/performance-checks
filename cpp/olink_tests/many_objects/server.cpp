#include "../helpers/prepare_test_services.h"

#include "olink/remotenode.h"
#include "olink/remoteregistry.h"
#include "olink/iobjectsource.h"
#include "olink/core/types.h"

#include "apigear/olink/olinkhost.h"

#include <memory>
#include <chrono>
#include <iostream>
#include <algorithm>

/*
Creates and runs olink server with a stub service, which only handles property changes.
It does not have any implementation for methods and doesn't emit signals.
It finishes work when it receives unlink messages for all services it provides.
It does not initiate any action, only responses for change property requests, so test scenario is controlled by client application.
Time measurements starts on first link message received and finishes on last unlink received.
*/
int main(int argc, char* argv[])
{
    ApiGear::ObjectLink::RemoteRegistry registry;

    auto portNumber = 8000;
    ApiGear::PocoImpl::OLinkHost testHost(registry, [](auto /*level*/, auto /*msg*/) {});
    testHost.listen(portNumber);
    auto begin = std::chrono::high_resolution_clock::now();

    auto services = prepareServices(registry);
    auto testStarted = false;

    auto servicesfinished = 0;
    do {

        servicesfinished = 0;
        for (auto& service : services)
        {
            if (!testStarted && service->m_status == ServiceStatus::LinkedRceived)
            {
                testStarted = true;
                begin = std::chrono::high_resolution_clock::now();
            }
            if (service->m_status == ServiceStatus::UnlinkedReceived)
            {
                servicesfinished++;
            }
        }

    } while (servicesfinished != services.size());

    auto end = std::chrono::high_resolution_clock::now();
    Poco::Thread::sleep(200);

    testHost.close();

    auto test_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "server finished work, time measured " << test_duration.count() << std::endl;
}
