#pragma once
#include "api/olink/olinktestapi0.h"

/*
* A wrapper for tested object that adds counting of incoming messages.
*/
class TestSink : public api::OLinkTestApi0
{
public:
    void olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value) override {
        propertyChangedTimes++;
        api::OLinkTestApi0::olinkOnPropertyChanged(propertyId, value);
    }

    void olinkOnInit(const std::string& objectId, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode* node) override
    {
        api::OLinkTestApi0::olinkOnInit(objectId, props, node);
        initReceived = true;
    }

    bool isReady()
    {
        return initReceived;
    }

    bool initReceived = false;
    uint32_t propertyChangedTimes = 0;
};
