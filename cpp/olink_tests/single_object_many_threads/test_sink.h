#pragma once
#include "api/generated/olink/testapi0client.h"

/*
* A wrapper for tested object that adds counting of incoming messages.
*/
class TestSink : public Cpp::Api::olink::TestApi0Client
{
public:
    void olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value) override {
        m_propertyChangedTimes++;
        Cpp::Api::olink::TestApi0Client::olinkOnPropertyChanged(propertyId, value);
    }

    uint32_t propertyChangedTimes() const
    {
        return m_propertyChangedTimes;
    }
    const std::string& objectName() const
    {
        static auto name = "MqttObject0";
        return name;
    }
private:
    uint32_t m_propertyChangedTimes = 0;
};
