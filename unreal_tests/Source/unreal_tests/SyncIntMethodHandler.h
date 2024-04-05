// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <future>
#include "Counter.h"
#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "AbstractTestBase.h"
#include "SyncIntMethodHandler.generated.h"

using chrono_hr_timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSyncIntMethodHandlerThresholdDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSyncIntMethodHandlerTaskEndedDelegate);

/**
 * Class used to execute an int method on the UApiTestApi0OLinkClient
 * in a synchronous matter, it sends next request only after object receives the response.
 * Configure the number of sent messages with @param messagesCount 
 * Configure the start number with @param startValue, each next request is increased with 1
 * Initialize must be called before use
 * 
 */
UCLASS()
class UNREAL_TESTS_API USyncIntMethodHandler : public UAbstractTestBase
{
	GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0, UCounter* mainCounter, int messagesCount);

    ~USyncIntMethodHandler();

    void cleanUp() override;

    /*Use this function to start executing int method in synchronous way*/
    void start(int startValue) override;

    UFUNCTION()
        void executeNextTask();

    UFUNCTION()
        int getCount();

    UPROPERTY(BlueprintAssignable, DisplayName = "Threshold Reached Delegate")
        FSyncIntMethodHandlerThresholdDelegate OnThresholdReached;
    UPROPERTY(BlueprintAssignable, DisplayName = "Task Ended Delegate")
        FSyncIntMethodHandlerTaskEndedDelegate OnTaskEnded;
    UPROPERTY(BlueprintReadWrite)
        int Threshold;

    std::vector<chrono_hr_timepoint>& getStartPoints() override;

    std::vector<chrono_hr_timepoint>& getStopPoints() override;

private:
    UApiTestApi0OLinkClient* m_clientApi0;
    std::atomic<int> m_counter{ 0 };
    std::atomic<int> m_currentValue{ 0 };
    UCounter* m_mainCounter;
    std::vector<chrono_hr_timepoint> m_startTimePoints;
    std::vector<chrono_hr_timepoint> m_stopTimePoints;
    std::vector<TSharedFuture<void>> m_futures;
};
