// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <future>
#include "Counter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestCounterThresholdDelegate);

/**
 * 
 */
UCLASS()
class UNREAL_TESTS_API UCounter : public UObject
{
	GENERATED_BODY()
public:

    UFUNCTION()
	void increaseInt(int notUsedPsrameter)
    {
        counter+=1;
        if (counter >= Threshold)
        {
            std::cout << "Threshold reached" << std::endl;
            OnThresholdReached.Broadcast();
        }
    }
    UFUNCTION()
    void increaseString(const FString& notUsedPsrameter)
    {
        counter+=1;
        if (counter >= Threshold)
        {
            std::cout << "Threshold reached" << std::endl;
            OnThresholdReached.Broadcast();
        }
    }
    UFUNCTION()
    void increaseFloat(const float notUsedPsrameter)
    {
        counter++;
        if (counter >= Threshold)
        {
            OnThresholdReached.Broadcast();
        }
    }
    UFUNCTION()
    int getCount()
    {
        return counter;
    }

    UPROPERTY(BlueprintAssignable, DisplayName = "Threshold Reached Delegate")
        FTestCounterThresholdDelegate OnThresholdReached;
    UPROPERTY(BlueprintReadWrite)
        int Threshold;
private:
    std::atomic<int> counter{ 0 };
};
