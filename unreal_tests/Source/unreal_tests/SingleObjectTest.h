// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <chrono>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SingleObjectTest.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, config = Game)
class UNREAL_TESTS_API USingleObjectTest : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void Execute();

	UFUNCTION()
	void FinishTest();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCounter* propertyChangeCounter;

	UPROPERTY(Config)
	int ThreadCount = 100;
	UPROPERTY(Config)
	int RequestsPerThread = 1000;
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
};
