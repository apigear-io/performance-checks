#pragma once


#include "TestBaseObject.h"
#include "AbstractTestBase.generated.h"


UCLASS(Abstract, NotBlueprintType)
class UAbstractTestBase : public UObject, public ITestBaseObject
{
	GENERATED_BODY()
public:
    void cleanUp()  override {}
    void start(int number) override {}
    std::vector<chrono_hr_timepoint>& getStartPoints() override { return m_startTimePoints; }
    std::vector<chrono_hr_timepoint>& getStopPoints() override { return m_stopTimePoints; }

protected:
    std::vector<chrono_hr_timepoint> m_startTimePoints;
    std::vector<chrono_hr_timepoint> m_stopTimePoints;
};
