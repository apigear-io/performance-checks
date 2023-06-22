#pragma once
#include "api/generated/olink/testapi0client.h"

/*
* A wrapper for tested object that adds counting of incoming messages.
*/
class TestSink : public Cpp::Api::olink::TestApi0Client
{
public:
    void olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value) override {
        propertyChangedTimes++;
        Cpp::Api::olink::TestApi0Client::olinkOnPropertyChanged(propertyId, value);
    }
    uint32_t propertyChangedTimes = 0;
};