#ifndef AYNC_INT_PROPERTY_TESTDATA_H
#define AYNC_INT_PROPERTY_TESTDATA_H

#include "itestsink.h"
#include "api/mqtt/mqtttestapi0.h"
#include "../../latency_helper/latency_helper.h"
#include <QtCore>

class PropertyIntTestData : public QObject
{
    Q_OBJECT
public:
    PropertyIntTestData(ApiGear::Mqtt::Client& client,
                        std::vector<chrono_hr_timepoint>& timeStart,
                        std::vector<chrono_hr_timepoint>& timeStop);

    void addStopTimeOnPropertyChanged(int value);
    void testFunction(uint32_t value);

    bool isReady() const;

    const QString objectName() const;

    bool allResponsesReceived(uint32_t messages_number) const;
private:
    std::vector<chrono_hr_timepoint>& m_timeStart;
    std::vector<chrono_hr_timepoint>& m_timeStop;
    std::shared_ptr<TestSink<api::MqttTestApi0,api::AbstractTestApi0>> sink;
};

#endif // AYNC_INT_PROPERTY_TESTDATA_H
