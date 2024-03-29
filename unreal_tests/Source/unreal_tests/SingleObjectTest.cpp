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

#include "ApiGearTicker.h"

static FString processMessageFunctionName = "FinishTest";
ApiGear::FDelegateHandle quitGamedelegate;


void calculateAndPrintLatencyParameters (const std::vector<chrono_hr_timepoint>& startPoints,
                                         const std::vector<chrono_hr_timepoint>& stopPoints)
{
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

    std::cout << "Latency[us]: mean " << std::fixed << std::setprecision(2) << mean << " max " <<max << " min " << min << std::endl;
    UE_LOG(LogTemp, Warning, TEXT("Latency[us]: mean %f max %d min %d"), mean, max, min);
}
void prepareStringMessages(std::vector<FString>& messagesToSend, int messages_number)
{
    for (int msgNo = 0u; msgNo < messages_number; msgNo++)
    {
        auto message = FString(std::string("Some longer property to be set, prepared before test for each message number to reduce allocating time in tests" + std::to_string(msgNo)).c_str());
        messagesToSend.push_back(message);
    }
}


void subscribeForPropertyChanges(UApiTestApi0OLinkClient* clientApi0,  UCounter* changesCounter) 
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


void USingleObjectTest::configureExecuteOperation(UApiTestApi0OLinkClient* clientApi0)
{
    if (TestPropertyType == 0)
    {
        std::cout << "Test for int property" << std::endl;
        if (TestOperationType == 0) // Set Property ASYNC
        {
            std::cout << "Property Async" << std::endl;
            executeTestOperation = [this](int startNumber) { executeAsyncPropertyIntTest(startNumber); };
            clientApi0->_GetSignals_Implementation()->OnPropIntChanged.AddDynamic(this, &USingleObjectTest::AddStopTimePointPropertyInt);
        }
        else if (TestOperationType == 1)// Set Property SYNC
        {
            std::cout << "Property Sync" << std::endl;
            m_syncIntPropertyHandler= NewObject<USyncIntPropertyHandler>(this, USyncIntPropertyHandler::StaticClass(), FName("USyncIntPropertyHandler"));
            m_syncIntPropertyHandler->initialize(clientApi0, RequestsPerThread);// TODO only works for one thread now
            executeTestOperation = [this](int startNumber) { m_syncIntPropertyHandler->start(startNumber); };
        }
        else if (TestOperationType == 2) // Call Method ASYNC
        {
            std::cout << "Method Async" << std::endl;
            executeTestOperation = [this](int startNumber) {executeAsyncMethodIntTest(startNumber); };
        }
        else if (TestOperationType == 3)// Call Method SYNC
        {
            std::cout << "Method Sync" << std::endl;
            m_syncMethodHandler= NewObject<USyncIntMethodHandler>(this, USyncIntMethodHandler::StaticClass(), FName("SyncIntMethodHandler"));
            m_syncMethodHandler->initialize(clientApi0, propertyChangeCounter, RequestsPerThread);// TODO only works for one thread now
            executeTestOperation = [this](int startNumber) { m_syncMethodHandler->start(startNumber); };
        }
    }
    else if (TestPropertyType == 2)
    {
        std::cout << "Test for float property" << std::endl;
        executeTestOperation = [this](int startNumber) {executeFloatTest(startNumber); };
    }
    else if (TestPropertyType == 1)
    {
        std::cout << "Test for string property" << std::endl;
        executeTestOperation = [this](int startNumber) {executeStringTest(startNumber); };
    }
}

void USingleObjectTest::AddStopTimePointPropertyInt(int number)
{
    int index = number - 1;
    m_stopTimePoints[index] = std::chrono::high_resolution_clock::now();
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
    prepareStringMessages(messagesToSend, messages_number);

    m_startTimePoints= std::vector<chrono_hr_timepoint>(messages_number, chrono_hr_timepoint());
    m_stopTimePoints =  std::vector<chrono_hr_timepoint>(messages_number, chrono_hr_timepoint());
    m_futures.reserve(messages_number);
    
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
            [clientApi0, this, threadNo]() {

                auto startNumber = threadNo * RequestsPerThread;
                executeTestOperation(startNumber);
            });
        tasks.push_back(sendMessagesTask.Share());
    }
    for (auto task : tasks)
    {
        task.Get();
    }
}

UApiTestApi0OLinkClient* USingleObjectTest::getClient0ApiSubsystem()
{
    auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
    UApiTestApi0OLinkClient* clientApi0 = gameInstance->GetSubsystem<UApiTestApi0OLinkClient>();
    return clientApi0;
}

void USingleObjectTest::FinishTest()
{
    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Time measured [ms]: " << time.count() << std::endl;
    UE_LOG(LogTemp, Warning, TEXT(" TIME MEASURED %d"), time.count());
    std::cout << "Objects number: 1" << std::endl;
    std::cout << "Function execution number for each object: " << ThreadCount * RequestsPerThread << std::endl;

    if (m_syncMethodHandler)
    {
        calculateAndPrintLatencyParameters(m_syncMethodHandler->getStartPoints(), m_syncMethodHandler->getStopPoints());
    }
    else if (m_syncIntPropertyHandler)
    {
        calculateAndPrintLatencyParameters(m_syncIntPropertyHandler->getStartPoints(), m_syncIntPropertyHandler->getStopPoints());
    }
    else 
    {
        calculateAndPrintLatencyParameters(m_startTimePoints, m_stopTimePoints);
    }

    auto clientApi0 = getClient0ApiSubsystem();
    unsubscribePropertyChanges(clientApi0, propertyChangeCounter);
    propertyChangeCounter->OnThresholdReached.RemoveDynamic(this, &USingleObjectTest::FinishTest);
    if (TestPropertyType == 0 && (TestOperationType == 0 || TestOperationType == 1))
    {
        clientApi0->_GetSignals_Implementation()->OnPropIntChanged.RemoveDynamic(this, &USingleObjectTest::AddStopTimePointPropertyInt);
    }


    quitGamedelegate = ApiGearTicker::GetCoreTicker().AddTicker(*processMessageFunctionName, 0,
        [this](float /*param*/)
        {
            for (auto& future : m_futures)
            {
                future.Get();
            }
            UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
            ApiGearTicker::GetCoreTicker().RemoveTicker(quitGamedelegate);
            return true;
        });
}


void USingleObjectTest::executeStringTest(int startNumber)
{
    auto clientApi0 = getClient0ApiSubsystem();
    for (auto i = 0; i < RequestsPerThread; i++)
    {
        auto number = startNumber + i;
        clientApi0->Execute_SetPropString(clientApi0, messagesToSend[number]);
    }
}
void USingleObjectTest::executeFloatTest(int startNumber)
{
    auto clientApi0 = getClient0ApiSubsystem();
    for (auto i = 0; i < RequestsPerThread; i++)
    {
        auto number = startNumber + i;
        clientApi0->Execute_SetPropFloat(clientApi0, number + 1.0f + number / 1000.0f);
    }
}

void USingleObjectTest::executeAsyncPropertyIntTest(int startNumber)
{
    auto clientApi0 = getClient0ApiSubsystem();
    for (auto i = 0; i < RequestsPerThread; i++)
    {
        auto number = startNumber + i;
        m_startTimePoints[number] = std::chrono::high_resolution_clock::now();
        clientApi0->Execute_SetPropInt(clientApi0, number+1);
    }
}

void USingleObjectTest::executeAsyncMethodIntTest(int startNumber)
{
    auto clientApi0 = getClient0ApiSubsystem();
    for (auto i = 0; i < RequestsPerThread; i++)
    {
        auto number = startNumber + i;
        m_futures.push_back(Async(EAsyncExecution::ThreadPool,
            [number, clientApi0, this]()
            {
                m_startTimePoints[number] = std::chrono::high_resolution_clock::now();
                clientApi0->Execute_FuncInt(clientApi0, number);
                m_stopTimePoints[number] = std::chrono::high_resolution_clock::now();
                propertyChangeCounter->increaseInt(number);
            }).Share());
    }
}


