/**
Tracer
Copyright (C) 2020 ApiGear UG
*/
#include "tracer.h"
#include "../utilities/logger.h"
#include <Poco/Dynamic/Var.h>
#include <Poco/Util/TimerTaskAdapter.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <iostream>
#include <sstream>

using namespace ApiGear::PocoImpl;

static bool isbusy = false;

Tracer::Tracer()
    : m_traceUrl(Poco::URI(""))
    , m_session(nullptr)
    , m_task(nullptr)
{
}

void Tracer::connect(const std::string& baseUrl, const std::string& identifier)
{
    std::string gatewayUrl = baseUrl+"/monitor/"+identifier+"/";
    m_traceUrl = Poco::URI(gatewayUrl);
    m_session = nullptr;
    if (!m_task.isNull())
    {
        m_task->cancel();
    }
    m_task = new Poco::Util::TimerTaskAdapter<Tracer>(*this, &Tracer::doProcess);
    m_retryTimer.schedule(m_task, 10, 5000);   
}

void Tracer::connect()
{
    if (m_traceUrl.getHost().empty()) {
        return;
    }
    if(m_session == nullptr) {
        try {
            m_session = new Poco::Net::HTTPClientSession(m_traceUrl.getHost(), m_traceUrl.getPort());
        } catch (std::exception &e) {
            m_session = nullptr;
            AG_LOG_ERROR("tracer doProcess Exception " + std::string(e.what()));
        }
    }
}

void Tracer::trace(const std::string &eventType, const std::string &symbol, const nlohmann::json &fields)
{
    nlohmann::json obj;
    obj["type"] = eventType;
    obj["symbol"] = symbol;
    obj["data"] = fields;

    m_queueMutex.lock(100);
    m_queue.push_back(obj);
    m_queueMutex.unlock();
    process();
}

void Tracer::call(const std::string &symbol, const nlohmann::json &fields)
{
    trace("call", symbol, fields);
}

void Tracer::signal(const std::string &symbol, const nlohmann::json &fields)
{
    trace("signal", symbol, fields);
}

void Tracer::state(const std::string &symbol, const nlohmann::json &fields)
{
    trace("state", symbol, fields);
}

void Tracer::process()
{
    if (!m_task.isNull())
    {
        m_task->cancel();
    }
    m_task = new Poco::Util::TimerTaskAdapter<Tracer>(*this, &Tracer::doProcess);
    m_retryTimer.schedule(m_task, 10, 5000);
}

void Tracer::doProcess(Poco::Util::TimerTask& task)
{
    if(isbusy) {
        AG_LOG_DEBUG("still busy ... skipping");
        return;
    }

    if (m_session == nullptr) {
        m_task->cancel();
        connect();
        m_task = new Poco::Util::TimerTaskAdapter<Tracer>(*this, &Tracer::doProcess);
        m_retryTimer.schedule(m_task, 100, 5000);
        return;
    }

    isbusy = true;
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, m_traceUrl.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);
    request.setKeepAlive(true);
    request.setContentType("application/json; charset=utf-8");
    Poco::Net::HTTPResponse response;
    nlohmann::json list;
    m_queueMutex.lock(100);
    if(m_queue.empty())
    {
        isbusy = false;
        m_queueMutex.unlock();
        return;
    }
    while(!m_queue.empty())
    {
        list.push_back(m_queue.front());
        m_queue.pop_front();
    }
    m_queueMutex.unlock();

    bool retry = false;
    try {
        request.setContentLength(list.dump().length());
        std::ostream& os = m_session->sendRequest(request);
        os << list;

        m_session->receiveResponse(response);
        if (response.getStatus() != 200) {
            retry = true;
        }
    } catch (std::exception &e) {
        retry = true;
        AG_LOG_ERROR("tracer doProcess Exception " + std::string(e.what()));
    }

    if(retry) {
        m_queueMutex.lock(100);
        for(const auto& entry: list) {
            m_queue.push_front(entry);
        }
        m_queueMutex.unlock();
        
        m_task->cancel();
        connect();
        m_task = new Poco::Util::TimerTaskAdapter<Tracer>(*this, &Tracer::doProcess);
        m_retryTimer.schedule(m_task, 5000, 5000);
    }
    isbusy = false;
}
