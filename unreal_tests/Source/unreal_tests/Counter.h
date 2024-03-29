// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <future>
#include "Counter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestCounterThresholdDelegate);

/**
 * Counts total execution of any increase method.
 * When count is equal to set Threshold it emits the OnThresholdReached delegate
 */
UCLASS()
class UNREAL_TESTS_API UCounter : public UObject
{
	GENERATED_BODY()
public:

    UFUNCTION()
        void increaseInt(int notUsedPsrameter);
    UFUNCTION()
        void increaseString(const FString& notUsedPsrameter);
    UFUNCTION()
        void increaseFloat(const float notUsedPsrameter);
 
    UFUNCTION()
        int getCount();

    UPROPERTY(BlueprintAssignable, DisplayName = "Threshold Reached Delegate")
        FTestCounterThresholdDelegate OnThresholdReached;
    UPROPERTY(BlueprintReadWrite)
        int Threshold;
private:
    std::atomic<int> counter{ 0 };
};
