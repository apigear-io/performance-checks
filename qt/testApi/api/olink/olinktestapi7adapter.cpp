/**
NO TITLE
Copyright (C) 2020 ApiGear UG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/



#include "olinktestapi7adapter.h"

#include <nlohmann/json.hpp>
#include "api/api/json.adapter.h"

#include "olink/remoteregistry.h"
#include "olink/iremotenode.h"
#include "utilities/logger.h"

#include <QtCore>

using namespace ApiGear::ObjectLink;

using json = nlohmann::json;

namespace api {

OLinkTestApi7Adapter::OLinkTestApi7Adapter(RemoteRegistry& registry, AbstractTestApi7* impl, QObject *parent)
    : QObject(parent)
    , m_impl(impl)
    , m_registry(registry)
{
    connect(m_impl, &AbstractTestApi7::propIntChanged, this,
        [=](int propInt) {
        const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
        for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(propertyId))) {
            auto lockedNode = node.lock();
            if(lockedNode) {
                lockedNode->notifyPropertyChange(propertyId, propInt);
            }
        }
    });
    connect(m_impl, &AbstractTestApi7::propFloatChanged, this,
        [=](qreal propFloat) {
        const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propFloat");
        for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(propertyId))) {
            auto lockedNode = node.lock();
            if(lockedNode) {
                lockedNode->notifyPropertyChange(propertyId, propFloat);
            }
        }
    });
    connect(m_impl, &AbstractTestApi7::propStringChanged, this,
        [=](const QString& propString) {
        const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propString");
        for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(propertyId))) {
            auto lockedNode = node.lock();
            if(lockedNode) {
                lockedNode->notifyPropertyChange(propertyId, propString);
            }
        }
    });
        connect(m_impl, &AbstractTestApi7::sigInt, this,
            [=](int paramInt) {
                const nlohmann::json& args = { paramInt };
                const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigInt");
                for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(signalId))) {
                    auto lockedNode = node.lock();
                    if(lockedNode) {
                        lockedNode->notifySignal(signalId, args);
                    }
                }
    });
        connect(m_impl, &AbstractTestApi7::sigFloat, this,
            [=](qreal paramFloat) {
                const nlohmann::json& args = { paramFloat };
                const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigFloat");
                for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(signalId))) {
                    auto lockedNode = node.lock();
                    if(lockedNode) {
                        lockedNode->notifySignal(signalId, args);
                    }
                }
    });
        connect(m_impl, &AbstractTestApi7::sigString, this,
            [=](const QString& paramString) {
                const nlohmann::json& args = { paramString };
                const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigString");
                for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(signalId))) {
                    auto lockedNode = node.lock();
                    if(lockedNode) {
                        lockedNode->notifySignal(signalId, args);
                    }
                }
    });
}

json OLinkTestApi7Adapter::captureState()
{
    return json::object({
        { "propInt", m_impl->propInt() },
        { "propFloat", m_impl->propFloat() },
        { "propString", m_impl->propString() }
    });
}

void OLinkTestApi7Adapter::applyState(const json& state)
{
    if(state.contains("propInt")) {
        m_impl->setPropInt(state["propInt"]);
    }
    if(state.contains("propFloat")) {
        m_impl->setPropFloat(state["propFloat"]);
    }
    if(state.contains("propString")) {
        m_impl->setPropString(state["propString"]);
    }
}


std::string OLinkTestApi7Adapter::olinkObjectName() {
    return "api.TestApi7";
}

json OLinkTestApi7Adapter::olinkInvoke(const std::string& methodId, const nlohmann::json& args){
    AG_LOG_DEBUG(Q_FUNC_INFO);
    AG_LOG_DEBUG(methodId);
    std::string path = Name::getMemberName(methodId);
    if(path == "funcInt") {
        const int& paramInt = args.at(0);
        int result = m_impl->funcInt(paramInt);
        return result;
    }
    if(path == "funcFloat") {
        const qreal& paramFloat = args.at(0);
        qreal result = m_impl->funcFloat(paramFloat);
        return result;
    }
    if(path == "funcString") {
        const QString& paramString = args.at(0);
        QString result = m_impl->funcString(paramString);
        return result;
    }
    return json();
}

void OLinkTestApi7Adapter::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value){
    AG_LOG_DEBUG(Q_FUNC_INFO);
    AG_LOG_DEBUG(propertyId);
    std::string path = Name::getMemberName(propertyId);
    if(path == "propInt") {
        int propInt = value.get<int>();
        m_impl->setPropInt(propInt);
    }
    if(path == "propFloat") {
        qreal propFloat = value.get<qreal>();
        m_impl->setPropFloat(propFloat);
    }
    if(path == "propString") {
        QString propString = value.get<QString>();
        m_impl->setPropString(propString);
    }    
}

void OLinkTestApi7Adapter::olinkLinked(const std::string& objectId, IRemoteNode *node) {
    AG_LOG_INFO(Q_FUNC_INFO);
    AG_LOG_INFO(objectId);
}

void OLinkTestApi7Adapter::olinkUnlinked(const std::string& objectId)
{
    AG_LOG_INFO(Q_FUNC_INFO);
    AG_LOG_INFO(objectId);
}

json OLinkTestApi7Adapter::olinkCollectProperties()
{
    return captureState();
}

} // namespace api
