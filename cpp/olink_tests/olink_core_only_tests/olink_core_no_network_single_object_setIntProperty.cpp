#include "olink/remotenode.h"
#include "olink/remoteregistry.h"
#include "olink/iobjectsource.h"
#include "olink/core/types.h"
#include "olink/clientnode.h"
#include "olink/clientregistry.h"
#include "api/generated/olink/testapi0client.h"
#include "api/generated/olink/testapi0service.h"
#include "api/implementation//testapi0.h"

#include "../helpers/inspected_sink.h"
#include "../helpers/latency_helpers.h"
#include "../helpers/olink_handler_no_network.hpp"
#include "../../scenario_templates/single_object_many_threads/executeTestFunction.h"

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
    PropertyIntTestData(std::vector<chrono_hr_timepoint>& latenciesStart,
        std::vector<chrono_hr_timepoint>& latenciesStop)
        :m_latenciesStart(latenciesStart),
        m_latenciesStop(latenciesStop)
    {
        olinkClient = std::make_shared<Cpp::Api::olink::TestApi0Client>();
        sink = std::make_shared<InspectedSink>(olinkClient);
        olinkClient->_getPublisher().subscribeToPropIntChanged([this](int propInt) 
            {
                auto index = propInt-1;
                m_latenciesStop[index]=std::chrono::high_resolution_clock::now();
                count++;
            });
    }
    void testFunction(uint32_t value)
    {
        m_latenciesStart[value] = std::chrono::high_resolution_clock::now();
        olinkClient->setPropInt(value +1);
    }
    bool allResponsesReceived (uint32_t sentRequestsNumber) const
    {
        return count == sentRequestsNumber;
    }

    std::vector<chrono_hr_timepoint>& m_latenciesStart;
    std::vector<chrono_hr_timepoint>& m_latenciesStop;

    uint32_t count=0;
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
    
    // Prepare service that will respond to requests
    auto service = std::make_shared<Cpp::Api::TestApi0>();
    auto olinkServiceAdapter = std::make_shared<Cpp::Api::olink::TestApi0Service>(service, remote_registry);
    remote_registry.addSource(olinkServiceAdapter);

    OLinkHandlerNoConnection olinkProtocolHandler(client_node);

    std::vector<chrono_hr_timepoint> m_latenciesStart(messages_number, std::chrono::steady_clock::time_point());
    std::vector<chrono_hr_timepoint> m_latenciesStop(messages_number, std::chrono::steady_clock::time_point());

    auto testObject = PropertyIntTestData(m_latenciesStart, m_latenciesStop);

    executeTestFunction(testObject, olinkProtocolHandler, messages_number, 1u);
    

    calculateAndPrintLatencyParameters(m_latenciesStart, m_latenciesStop);
}
