// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleObjectTest.h"
#include "Generated/OLink/ApiTestApi0OLinkClient.h"
#include "Generated/api/AbstractApiTestApi0.h"
#include "TestBaseObject.h"
#include "AsyncIntMethodTest.h"
#include "AsyncFloatPropertyTest.h"
#include "AsyncIntPropertyTest.h"
#include "AsyncStringPropertyTest.h"
#include "Counter.h"

#include <memory>
#include <thread>
#include <vector>
#include <future>
#include <chrono>

#include "Logging/LogMacros.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ApiGearTicker.h"

static FString processMessageFunctionName = "FinishTest";
ApiGear::FDelegateHandle quitGamedelegate;

namespace {

    void calculateAndPrintLatencyParameters(const std::vector<chrono_hr_timepoint>& startPoints,
        const std::vector<chrono_hr_timepoint>& stopPoints)
    {
        if (startPoints.size() == 0 || stopPoints.size() == 0)
        {
            return;
        }
        uint64_t sum = 0;
        uint32_t min = std::chrono::duration_cast<std::chrono::microseconds>(stopPoints[0] - startPoints[0]).count();
        uint32_t max = 0;
        for (size_t i = 0; i < startPoints.size(); i++)
        {
            auto latency = std::chrono::duration_cast<std::chrono::microseconds>(stopPoints[i] - startPoints[i]).count();
            sum = sum + latency;
            if (min > latency) { min = latency; }
            if (max < latency) { max = latency; }
        }
        auto mean = double(sum) / startPoints.size();

        std::cout << "Latency[us]: mean " << std::fixed << std::setprecision(2) << mean << " max " << max << " min " << min << std::endl;
        UE_LOG(LogTemp, Warning, TEXT("Latency[us]: mean %f max %d min %d"), mean, max, min);
    }


    void subscribeForPropertyChanges(UApiTestApi0OLinkClient* clientApi0, UCounter* changesCounter)
    {
        clientApi0->_GetSignals_Implementation()->OnPropIntChanged.AddDynamic(changesCounter, &UCounter::increaseInt);
        clientApi0->_GetSignals_Implementation()->OnPropFloatChanged.AddDynamic(changesCounter, &UCounter::increaseFloat);
        clientApi0->_GetSignals_Implementation()->OnPropStringChanged.AddDynamic(changesCounter, &UCounter::increaseString);
    }

    void unsubscribePropertyChanges(UApiTestApi0OLinkClient* clientApi0, UCounter* changesCounter)
    {
        clientApi0->_GetSignals_Implementation()->OnPropIntChanged.RemoveDynamic(changesCounter, &UCounter::increaseInt);
        clientApi0->_GetSignals_Implementation()->OnPropFloatChanged.RemoveDynamic(changesCounter, &UCounter::increaseFloat);
        clientApi0->_GetSignals_Implementation()->OnPropStringChanged.RemoveDynamic(changesCounter, &UCounter::increaseString);
    }
}

void USingleObjectTest::configureExecuteOperation(UApiTestApi0OLinkClient* clientApi0)
{
    if (TestPropertyType == 0)// Int Data Type
    {
        std::cout << "Test for int property" << std::endl;
        if (TestOperationType == 0) // Set Property ASYNC
        {
            std::cout << "Property Async" << std::endl;
            auto asyncIntPropertyHandler = NewObject<UAsyncIntPropertyTest>(this);
            asyncIntPropertyHandler->initialize(clientApi0, RequestsPerThread, ThreadCount);

            m_test.SetInterface(asyncIntPropertyHandler);
            m_test.SetObject(asyncIntPropertyHandler);

        }
        else if (TestOperationType == 1)// Set Property SYNC
        {
            std::cout << "Property Sync" << std::endl;
            auto syncIntPropertyHandler = NewObject<USyncIntPropertyHandler>(this);
            syncIntPropertyHandler->initialize(clientApi0, RequestsPerThread);// TODO only works for one thread now
            m_test.SetInterface(syncIntPropertyHandler);
            m_test.SetObject(syncIntPropertyHandler);
        }
        else if (TestOperationType == 2) // Call Method ASYNC
        {
            std::cout << "Method Async" << std::endl;
            auto asyncMethodTest = NewObject<UAsyncIntMethodTest>(this);
            asyncMethodTest->initialize(clientApi0, propertyChangeCounter, RequestsPerThread, ThreadCount);
            m_test.SetInterface(asyncMethodTest);
            m_test.SetObject(asyncMethodTest);
        }
        else if (TestOperationType == 3)// Call Method SYNC
        {
            std::cout << "Method Sync" << std::endl;
            auto syncMethodHandler= NewObject<USyncIntMethodHandler>(this);
            syncMethodHandler->initialize(clientApi0, propertyChangeCounter, RequestsPerThread);// TODO only works for one thread now
            m_test.SetInterface(syncMethodHandler);
            m_test.SetObject(syncMethodHandler);
        }
    }
    else if (TestPropertyType == 2)
    {
        std::cout << "Test for float property, async" << std::endl;
        auto floatPropTest = NewObject<UAsyncFloatPropertyTest>(this);
        floatPropTest->initialize(clientApi0, RequestsPerThread, ThreadCount);
        m_test.SetInterface(floatPropTest);
        m_test.SetObject(floatPropTest);
    }
    else if (TestPropertyType == 1)
    {
        std::cout << "Test for string property, async" << std::endl;
        auto stringPropTest = NewObject<UAsyncStringPropertyTest>(this);
        stringPropTest->initialize(clientApi0, RequestsPerThread, ThreadCount);
        m_test.SetInterface(stringPropTest);
        m_test.SetObject(stringPropTest);
    }
}

void USingleObjectTest::Execute()
{
    auto clientApi0 = getClient0ApiSubsystem();
    if (!clientApi0->_IsSubscribed())
    {
        UE_LOG(LogTemp, Warning, TEXT("Dropping test execution. Test can be executed only when the OLinkConnection is established. Please check the connection and make sure there is service object for this client") );
        return;
    }

    auto messages_number = ThreadCount * RequestsPerThread;
    
    propertyChangeCounter = NewObject<UCounter>(this, UCounter::StaticClass(), FName("propertyChangedCounter"));
    propertyChangeCounter->Threshold = messages_number;
    propertyChangeCounter->OnThresholdReached.AddDynamic(this, &USingleObjectTest::FinishTest);

    configureExecuteOperation(clientApi0);//Must be executed before subscribeForPropertyChanges, the order of adding callbacks for setting property matters
    subscribeForPropertyChanges(clientApi0, propertyChangeCounter);

    std::vector<TSharedFuture<void>> tasks;
    begin = std::chrono::high_resolution_clock::now();

    for (int threadNo = 0; threadNo < ThreadCount; threadNo++)
    {
        auto sendMessagesTask = Async(EAsyncExecution::ThreadPool,
            [this, threadNo]() {
                auto startNumber = threadNo * RequestsPerThread;
                m_test->start(startNumber);
            });
        tasks.push_back(sendMessagesTask.Share());
    }
    for (auto task : tasks)
    {
        task.Get();
    }
}

void USingleObjectTest::FinishTest()
{
    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Time measured [ms]: " << time.count() << std::endl;
    UE_LOG(LogTemp, Warning, TEXT(" TIME MEASURED %d"), time.count());
    std::cout << "Objects number: 1" << std::endl;
    std::cout << "Function execution number for each object: " << ThreadCount * RequestsPerThread << std::endl;

    calculateAndPrintLatencyParameters(m_test->getStartPoints(), m_test->getStopPoints());

    auto clientApi0 = getClient0ApiSubsystem();
    unsubscribePropertyChanges(clientApi0, propertyChangeCounter);
    propertyChangeCounter->OnThresholdReached.RemoveDynamic(this, &USingleObjectTest::FinishTest);

    quitGamedelegate = ApiGearTicker::GetCoreTicker().AddTicker(*processMessageFunctionName, 0,
        [this](float /*param*/)
        {
            m_test->cleanUp();
            UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
            ApiGearTicker::GetCoreTicker().RemoveTicker(quitGamedelegate);
            return true;
        });
}

UApiTestApi0OLinkClient* USingleObjectTest::getClient0ApiSubsystem()
{
    auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
    UApiTestApi0OLinkClient* clientApi0 = gameInstance->GetSubsystem<UApiTestApi0OLinkClient>();
    return clientApi0;
}
