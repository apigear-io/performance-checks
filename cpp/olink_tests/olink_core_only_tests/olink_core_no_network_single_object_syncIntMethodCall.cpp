#include "olink/remotenode.h"
#include "olink/remoteregistry.h"
#include "olink/iobjectsource.h"
#include "olink/core/types.h"
#include "olink/clientnode.h"
#include "olink/clientregistry.h"
#include "api/generated/olink/testapi0client.h"
#include "api/generated/olink/testapi0service.h"
#include "api/implementation//testapi0.h"

#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"
#include "../helpers/inspected_sink.h"
#include "../helpers/latency_helpers.h"
#include "../helpers/olink_handler_no_network.hpp"

#include <memory>
#include <chrono>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>


class PropertyIntTestData
{
public:
    PropertyIntTestData(std::vector<uint32_t>& latencies)
        :m_latencies(latencies)
    {
        olinkClient = std::make_shared<Cpp::Api::olink::TestApi0Client>();
        sink = std::make_shared<InspectedSink>(olinkClient);
    }
    void testFunction(uint32_t value)
    {
        auto start = std::chrono::high_resolution_clock::now();
        olinkClient->funcInt(value);
        auto end = std::chrono::high_resolution_clock::now();

        m_latencies[value] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return true;
    }

    std::vector<uint32_t>& m_latencies;
    std::shared_ptr<Cpp::Api::olink::TestApi0Client> olinkClient;
    std::shared_ptr<InspectedSink> sink;
};


int main(int argc, char* argv[])
{
    auto messages_number = 1000u;
    if (argc > 1)
    {
        char* p;
        messages_number = strtol(argv[1], &p, 10);
    }

    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto client_node = ApiGear::ObjectLink::ClientNode::create(client_registry);

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remote_node = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);

    //Connect directly sending and receiving messages, not with a network.
    remote_node->onWrite([client_node](const auto& msg) { client_node->handleMessage(msg); });
    client_node->onWrite([remote_node](const auto& msg) { remote_node->handleMessage(msg); });
    
    auto service = std::make_shared<Cpp::Api::TestApi0>();
    auto olinkServiceAdapter = std::make_shared<Cpp::Api::olink::TestApi0Service>(service, remote_registry);
    remote_registry.addSource(olinkServiceAdapter);

    OLinkHandlerNoConnection olinkProtocolHandler(client_node);

    std::vector<uint32_t> latencies(messages_number,0);
    auto testObject = PropertyIntTestData(latencies);
    executeTestFunction(testObject, olinkProtocolHandler, messages_number, 1u);

    calculateAndPrintLatencyParameters(latencies);

}
