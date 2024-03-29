// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <future>
#include "Counter.h"
#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "SyncIntPropertyHandler.generated.h"

using chrono_hr_timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSyncIntPropertyHandlerThresholdDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSyncIntPropertyHandlerTaskEndedDelegate);

/**
 * Class used to execute an int property change request on UApiTestApi0OLinkClient
 * in a synchronous matter, it sends next request only after object receives the response.
 * Configure the number of sent messages with @param messagesCount 
 * Configure the start number with @param startValue, each next request is increased with 1
 * Initialize must be called before use, also make sure that the initialize method is called before you add 
 * a stop test condition to delegate in UApiTestApi0OLinkClient "OnPropIntChanged"
 * 
 */
UCLASS()
class UNREAL_TESTS_API USyncIntPropertyHandler : public UObject
{
	GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0, int startValue, int messagesCount);
    /*Use this function to start executing set int property in a synchronous way*/
    void start() { executeNextTask(); }

    UFUNCTION()
        void onPropertyChangeReceived(int number);

    UFUNCTION()
        void executeNextTask();

    UFUNCTION()
        int getCount();

    UPROPERTY(BlueprintAssignable, DisplayName = "Threshold Reached Delegate")
        FSyncIntPropertyHandlerThresholdDelegate OnThresholdReached;
    UPROPERTY(BlueprintAssignable, DisplayName = "Task Ended Delegate")
        FSyncIntPropertyHandlerTaskEndedDelegate OnTaskEnded;
    UPROPERTY(BlueprintReadWrite)
        int Threshold;

    std::vector<chrono_hr_timepoint>& getStartPoints();
    std::vector<chrono_hr_timepoint>& getStopPoints();

private:
    UApiTestApi0OLinkClient* m_clientApi0;
    std::atomic<int> counter{ 0 };
    std::atomic<int> currentNumber = { 0 };
    std::vector<chrono_hr_timepoint> m_startTimePoints;
    std::vector<chrono_hr_timepoint> m_stopTimePoints;
};
