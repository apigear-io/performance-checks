// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <chrono>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <vector>
#include <chrono>
#include <functional>
#include "SyncIntMethodHandler.h"
#include "SyncIntPropertyHandler.h"
#include "TestBaseObject.h"
#include "SingleObjectTest.generated.h"

using chrono_hr_timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

class UApiTestApi0OLinkClient;


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
	int ThreadCount = 1;
	UPROPERTY(Config)
	int RequestsPerThread = 10;
	/*
	 * TestPropertyType 0 -> test property type is int 
	 * TestPropertyType 1 -> test property type is string
	 * TestPropertyType 2 -> test property type is float
	 */
	UPROPERTY(Config)
	int TestPropertyType = 0;

	/*  
	* TestOperationType is used only for int type, it is ignored for other types
	* TestOperationType 0 is set property async
	* TestOperationType 1 is set property sync
	* TestOperationType 2 is execute method async
	* TestOperationType 3 is execute method sync
	*/
	UPROPERTY(Config)
	int TestOperationType = 0;

private:
	UPROPERTY()
	TScriptInterface<ITestBaseObject> m_test= nullptr;

	void configureExecuteOperation(UApiTestApi0OLinkClient* clientApi0);
	UApiTestApi0OLinkClient* getClient0ApiSubsystem();

	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
};
