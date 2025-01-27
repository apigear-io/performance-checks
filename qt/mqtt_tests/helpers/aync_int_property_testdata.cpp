#include "aync_int_property_testdata.h"
#include <QtCore>


PropertyIntTestData::PropertyIntTestData(ApiGear::Mqtt::Client& client,
                        std::vector<chrono_hr_timepoint>& timeStart,
                        std::vector<chrono_hr_timepoint>& timeStop)
        :m_timeStart(timeStart),
        m_timeStop(timeStop)
    {
        sink =  std::make_shared<TestSink<api::MqttTestApi0,api::AbstractTestApi0>>(client);
        api::MqttTestApi0::connect(sink.get(),
                                   &api::MqttTestApi0::propIntChanged,
                                   this,
                                   &PropertyIntTestData::addStopTimeOnPropertyChanged,
                                   Qt::QueuedConnection);
    }

    void PropertyIntTestData::addStopTimeOnPropertyChanged(int value)
    {
        auto index = value -1;
        m_timeStop[index] = std::chrono::high_resolution_clock::now();
    }

    void PropertyIntTestData::testFunction(uint32_t value)
    {
        m_timeStart[value]=std::chrono::high_resolution_clock::now();
        // Add one, to avoid setting property to 0 as first call, 0 is default property and it won't be set for same value.
        sink->setPropInt(value + 1);
    }

    bool PropertyIntTestData::isReady() const
    {
        return sink->isReady();
    }

    const QString PropertyIntTestData::objectName() const
    {
        return sink->objectName();
    }

    bool PropertyIntTestData::allResponsesReceived(uint32_t messages_number) const
    {
        return sink->allResponsesReceived(messages_number);
    }
