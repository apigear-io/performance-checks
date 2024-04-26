#pragma once

#include "olink/clientnode.h"
#include "olink/clientregistry.h"
#include <string>
#include <memory>
#include <iostream>

class OLinkHandlerNoConnection
{
public:
    OLinkHandlerNoConnection(std::shared_ptr<ApiGear::ObjectLink::ClientNode> client_node)
        :m_client_node(client_node)
    
    {
        m_client_node->setLogLevel(ApiGear::ObjectLink::LogLevel::Warning);
        ApiGear::ObjectLink::WriteLogFunc log = [](auto lvl, auto& msg) { if (lvl <= ApiGear::ObjectLink::LogLevel::Warning) std::cout << msg << std::endl; };
        m_client_node->onLog(log);
    }

    void prepareConnection(){}

    template<class TestData>
    void connectObjects(TestData& testData)
    {
        m_client_node->registry().addSink(testData.sink);
        m_client_node->linkRemote(testData.sink->olinkObjectName());
    }

    template<class TestData>
    void disconnectObjects(TestData& testData)
    {
        m_client_node->unlinkRemote(testData.sink->olinkObjectName());
        m_client_node->registry().removeSink(testData.sink->olinkObjectName());
    }

    template<class TestData>
    void waitForReturnMessages(TestData& testData, uint32_t messages_number)
    {
        while (!testData.allResponsesReceived(messages_number)){}
    }

    template<class TestData>
    void waitUntilObjectConnected(const TestData& object){}

private:
    std::shared_ptr<ApiGear::ObjectLink::ClientNode> m_client_node;
};
