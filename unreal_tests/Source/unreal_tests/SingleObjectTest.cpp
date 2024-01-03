// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleObjectTest.h"
#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "Generated/api/AbstractApiTestApi0.h"
#include <memory>
#include <thread>
#include <vector>
#include <future>
#include <chrono>
#include "Logging/LogMacros.h"
#include "Counter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void USingleObjectTest::Execute()
{

    auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
    UApiTestApi0OLinkClient* clientApi0 = gameInstance->GetSubsystem<UApiTestApi0OLinkClient>();
    if (!clientApi0->_IsSubscribed())
    {
        UE_LOG(LogTemp, Warning, TEXT("Dropping test execution. Test can be executed only when the OLinkConnection is established. Please check the connection and make sure there is service object for this client") );
        return;
    }
    propertyChangeCounter = NewObject<UCounter>(this, UCounter::StaticClass(), FName("propertyChangedCounter"));
    auto messages_number = ThreadCount * RequestsPerThread;
    propertyChangeCounter->Threshold = messages_number;

    clientApi0->_GetSignals_Implementation()->OnPropIntChanged.AddDynamic(propertyChangeCounter, &UCounter::increase);
    propertyChangeCounter->OnThresholdReached.AddDynamic(this, &USingleObjectTest::FinishTest);

    std::vector<std::shared_future<void>> tasks;
    begin = std::chrono::high_resolution_clock::now();

    for (int threadNo = 0; threadNo < ThreadCount; threadNo++)
    {
        auto sendMessagesTask = std::async(std::launch::async,
            [&clientApi0, this, threadNo]() {

                for (auto i = 0; i < RequestsPerThread; i++)
                {
                    auto number = threadNo * RequestsPerThread + i + 1;
                    clientApi0->Execute_SetPropInt(clientApi0, number);
                }
            });
        tasks.push_back(sendMessagesTask.share());
    }
    UE_LOG(LogTemp, Warning, TEXT(" ALL MESSAGES SENT"));
    for (auto task : tasks)
    {
        task.wait();
    }
    auto allMessagesReceived = false;

    UE_LOG(LogTemp, Warning, TEXT("WAITING FOR MESSAGES"));

}
void USingleObjectTest::FinishTest()
{
    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Time measured: " << time.count() << std::endl;
    UE_LOG(LogTemp, Warning, TEXT(" TIME MEASURED %d"), time.count());
    std::cout << "Objects number: 1" << std::endl;
    std::cout << "Function execution number for each object: " << ThreadCount * RequestsPerThread << std::endl;
    
    auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
    UApiTestApi0OLinkClient* clientApi0 = gameInstance->GetSubsystem<UApiTestApi0OLinkClient>();
    
    clientApi0->_GetSignals_Implementation()->OnPropIntChanged.RemoveDynamic(propertyChangeCounter, &UCounter::increase);
    propertyChangeCounter->OnThresholdReached.RemoveDynamic(this, &USingleObjectTest::FinishTest);

    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
