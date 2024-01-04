// Copyright Epic Games, Inc. All Rights Reserved.


#include "unreal_testsGameModeBase.h"
#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "Kismet/GameplayStatics.h"
#include "AssetCompilingManager.h"
#include <iostream>
#include "SingleObjectTest.h"

void Aunreal_testsGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);    

    auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
    UApiTestApi0OLinkClient* clientApi0 = gameInstance->GetSubsystem<UApiTestApi0OLinkClient>();
    clientApi0->_SubscriptionStatusdChanged.AddDynamic(this, &Aunreal_testsGameModeBase::ConnectionIsReady);

    
    UWorld* world = GetWorld();
    FAssetCompilingManager::Get().FinishAllCompilation();
    bIsAllAlreadyLoaded = true;
    if (bShouldExecuteTest)
    {
        std::cout << "All loaded running waiting test" << std::endl;
        bIsExecutingTest = true;
        bIsAllAlreadyLoaded = false;
        TestObject->Execute();
    }
}

Aunreal_testsGameModeBase::Aunreal_testsGameModeBase()
{
    TestObject = NewObject<USingleObjectTest>(this, USingleObjectTest::StaticClass(), FName("TestObject"));

}

void Aunreal_testsGameModeBase::ConnectionIsReady(bool IsSubscribed)
{
    if (IsSubscribed)
    {
        if (!bIsExecutingTest)
        {
            if (bIsAllAlreadyLoaded)
            {
                bIsExecutingTest = true;
                std::cout << "Connection status changed to subscribed, executing test" << std::endl;
                TestObject->Execute();
            }
            else 
            {
                std::cout<< "WAITING FOR ALL TO LOADED" << std::endl;
                bShouldExecuteTest = true;
            }
        }
        else 
        {
            UE_LOG(LogTemp, Warning, TEXT("Already running test"));
        }
    }
}

