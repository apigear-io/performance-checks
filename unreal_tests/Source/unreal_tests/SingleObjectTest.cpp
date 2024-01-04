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

    for (int msgNo = 0u; msgNo < ThreadCount * (RequestsPerThread + 1); msgNo++)
    {
        auto message = FString(std::string("Some longer property to be set, prepared before test for each message number to reduce allocating time in tests" + std::to_string(msgNo)).c_str());
        messagesToSend.push_back(message);
    }

    if (TestPropertyType == 1)
    {
        std::cout << "Test for string property" << std::endl;
        setPropertyExecution = [&clientApi0, this](int number)
        {
            clientApi0->Execute_SetPropString(clientApi0, messagesToSend[number]);
        };
    }
    else if (TestPropertyType == 2)
    {
        std::cout << "Test for float property" << std::endl;
        setPropertyExecution = [&clientApi0](int number)
        {
            clientApi0->Execute_SetPropFloat(clientApi0, number + 1.0f + number/1000.0f);
        };
    }
    else
    {
        std::cout << "Test for int property" << std::endl;
        setPropertyExecution = [&clientApi0](int number)
        {
            clientApi0->Execute_SetPropInt(clientApi0, number +1);
        };
    }

    clientApi0->_GetSignals_Implementation()->OnPropIntChanged.AddDynamic(propertyChangeCounter, &UCounter::increaseInt);
    clientApi0->_GetSignals_Implementation()->OnPropFloatChanged.AddDynamic(propertyChangeCounter, &UCounter::increaseFloat);
    clientApi0->_GetSignals_Implementation()->OnPropStringChanged.AddDynamic(propertyChangeCounter, &UCounter::increaseString);
    propertyChangeCounter->OnThresholdReached.AddDynamic(this, &USingleObjectTest::FinishTest);

    std::vector<std::shared_future<void>> tasks;
    begin = std::chrono::high_resolution_clock::now();

    for (int threadNo = 0; threadNo < ThreadCount; threadNo++)
    {
        auto sendMessagesTask = std::async(std::launch::async,
            [&clientApi0, this, threadNo]() {

                for (auto i = 0; i < RequestsPerThread; i++)
                {
                    auto number = threadNo * RequestsPerThread + i;
                    setPropertyExecution(number);
                    //clientApi0->Execute_SetPropInt(clientApi0, number+1);
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
    
    clientApi0->_GetSignals_Implementation()->OnPropIntChanged.RemoveDynamic(propertyChangeCounter, &UCounter::increaseInt);
    clientApi0->_GetSignals_Implementation()->OnPropFloatChanged.RemoveDynamic(propertyChangeCounter, &UCounter::increaseFloat);
    clientApi0->_GetSignals_Implementation()->OnPropStringChanged.RemoveDynamic(propertyChangeCounter, &UCounter::increaseString);
    propertyChangeCounter->OnThresholdReached.RemoveDynamic(this, &USingleObjectTest::FinishTest);

    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
