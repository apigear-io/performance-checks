// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "unreal_testsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_TESTS_API Aunreal_testsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	Aunreal_testsGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USingleObjectTest* TestObject;


	UFUNCTION()
	void ConnectionIsReady(bool IsSubscribed);
private:
	bool bIsExecutingTest = false;
	bool bShouldExecuteTest = false;
	bool bIsAllAlreadyLoaded = false;
};
