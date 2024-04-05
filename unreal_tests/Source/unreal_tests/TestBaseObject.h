#pragma once

#include <vector>
#include <chrono>
#include "UObject/Interface.h"
#include "TestBaseObject.generated.h"

using chrono_hr_timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;


UINTERFACE(MinimalAPI)
class UTestBaseObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface ITestBaseObject
 */
class ITestBaseObject
{
	GENERATED_BODY()
public:
    virtual void cleanUp() = 0;
    virtual void start(int number) = 0;
    virtual std::vector<chrono_hr_timepoint>& getStartPoints()  = 0;
    virtual std::vector<chrono_hr_timepoint>& getStopPoints()  = 0;
};
