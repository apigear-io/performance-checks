// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <future>
#include "Counter.h"
#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "SyncIntMethodHandler.generated.h"

using chrono_hr_timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSyncIntMethodHandlerThresholdDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSyncIntMethodHandlerTaskEndedDelegate);

/**
 * 
 */
UCLASS()
class UNREAL_TESTS_API USyncIntMethodHandler : public UObject
{
	GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0,
                    int startValue,
                    int messagesCount,
                    UCounter* mainCounter)
    {
        Threshold = messagesCount;
        m_clientApi0= clientApi0;
        m_currentValue = startValue;
        m_mainCounter = mainCounter;
        m_startTimePoints= std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
        m_stopTimePoints =  std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
        OnTaskEnded.AddDynamic(this, &USyncIntMethodHandler::executeNextTask);
        m_futures.reserve(messagesCount);
    }

    ~USyncIntMethodHandler()
    {
        for (auto& future : m_futures)
        {
            future.Get();
        }
    }

    UFUNCTION()
	void executeNextTask()
    {
        m_futures.push_back(Async(EAsyncExecution::ThreadPool,
            [this]()
            {
                m_startTimePoints[m_counter] = std::chrono::high_resolution_clock::now();
                m_clientApi0->Execute_FuncInt(m_clientApi0, m_currentValue);
                m_stopTimePoints[m_counter] = std::chrono::high_resolution_clock::now();
                m_counter+=1;
                m_currentValue+=1;
                m_mainCounter->increaseInt(m_currentValue);
                if (m_counter < Threshold)
                {
                    OnTaskEnded.Broadcast();
                }
                else 
                {
                    OnTaskEnded.RemoveDynamic(this, &USyncIntMethodHandler::executeNextTask);
                    OnThresholdReached.Broadcast();
                }
            }).Share());
    }

    UFUNCTION()
    int getCount()
    {
        return m_counter;
    }

    UPROPERTY(BlueprintAssignable, DisplayName = "Threshold Reached Delegate")
        FSyncIntMethodHandlerThresholdDelegate OnThresholdReached;
    UPROPERTY(BlueprintAssignable, DisplayName = "Task Ended Delegate")
        FSyncIntMethodHandlerTaskEndedDelegate OnTaskEnded;
    UPROPERTY(BlueprintReadWrite)
        int Threshold;

    std::vector<chrono_hr_timepoint>& getStartPoints()
    {
        return m_startTimePoints;
    }

    std::vector<chrono_hr_timepoint>& getStopPoints()
    {
        return m_stopTimePoints;
    }

private:
    UApiTestApi0OLinkClient* m_clientApi0;
    std::atomic<int> m_counter{ 0 };
    std::atomic<int> m_currentValue{ 0 };
    UCounter* m_mainCounter;
    std::vector<chrono_hr_timepoint> m_startTimePoints;
    std::vector<chrono_hr_timepoint> m_stopTimePoints;
    std::vector<TSharedFuture<void>> m_futures;
};
