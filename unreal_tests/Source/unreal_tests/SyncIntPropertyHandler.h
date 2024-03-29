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
 * 
 */
UCLASS()
class UNREAL_TESTS_API USyncIntPropertyHandler : public UObject
{
	GENERATED_BODY()
public:
    void initialize(UApiTestApi0OLinkClient* clientApi0,
                    int startValue,
                    int messagesCount)
    {
        Threshold = messagesCount;
        m_clientApi0= clientApi0;
        currentNumber = startValue +1;//Changes are not sent if request is for already set property. Default value for Int is "0", in test we always add 1 for setting int property to make sure value is always set.
        m_startTimePoints= std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
        m_stopTimePoints =  std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
        OnTaskEnded.AddDynamic(this, &USyncIntPropertyHandler::executeNextTask);
        m_clientApi0->_GetSignals_Implementation()->OnPropIntChanged.AddDynamic(this, &USyncIntPropertyHandler::onPropertyChangeReceived);
    }

    UFUNCTION()
    void onPropertyChangeReceived(int number)
    {
        if (number == currentNumber)
        {
            m_stopTimePoints[counter] = std::chrono::high_resolution_clock::now();
            counter+=1;
            currentNumber+=1;
        }
        else { return; }

        if (counter == Threshold)
        {
            OnTaskEnded.RemoveDynamic(this, &USyncIntPropertyHandler::executeNextTask);
            OnThresholdReached.Broadcast();
        }
        else 
        {
            OnTaskEnded.Broadcast();
        }
    }

    UFUNCTION()
	void executeNextTask()
    {
        m_startTimePoints[counter] = std::chrono::high_resolution_clock::now();
        m_clientApi0->Execute_SetPropInt(m_clientApi0, currentNumber);
    }

    UFUNCTION()
    int getCount()
    {
        return counter;
    }

    UPROPERTY(BlueprintAssignable, DisplayName = "Threshold Reached Delegate")
        FSyncIntPropertyHandlerThresholdDelegate OnThresholdReached;
    UPROPERTY(BlueprintAssignable, DisplayName = "Task Ended Delegate")
        FSyncIntPropertyHandlerTaskEndedDelegate OnTaskEnded;
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
    std::atomic<int> counter{ 0 };
    std::atomic<int> currentNumber = { 0 };
    std::vector<chrono_hr_timepoint> m_startTimePoints;
    std::vector<chrono_hr_timepoint> m_stopTimePoints;
};
