// Fill out your copyright notice in the Description page of Project Settings.

#include "SyncIntMethodHandler.h"

void USyncIntMethodHandler::initialize(UApiTestApi0OLinkClient* clientApi0,
                int startValue,
                int messagesCount,
                UCounter* mainCounter)
{
    Threshold = messagesCount;
    m_clientApi0= clientApi0;
    m_currentValue = startValue;
    m_mainCounter = mainCounter;
    m_startTimePoints= std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
    m_stopTimePoints =  std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
    OnTaskEnded.AddDynamic(this, &USyncIntMethodHandler::executeNextTask);
    m_futures.reserve(messagesCount);
}

USyncIntMethodHandler::~USyncIntMethodHandler()
{
    for (auto& future : m_futures)
    {
        future.Get();
    }
}

void USyncIntMethodHandler::executeNextTask()
{
    m_futures.push_back(Async(EAsyncExecution::ThreadPool,
        [this]()
        {
            m_startTimePoints[m_counter] = std::chrono::high_resolution_clock::now();
            m_clientApi0->Execute_FuncInt(m_clientApi0, m_currentValue);
            m_stopTimePoints[m_counter] = std::chrono::high_resolution_clock::now();
            m_counter+=1;
            m_currentValue+=1;
            m_mainCounter->increaseInt(m_currentValue);
            if (m_counter < Threshold)
            {
                OnTaskEnded.Broadcast();
            }
            else 
            {
                OnTaskEnded.RemoveDynamic(this, &USyncIntMethodHandler::executeNextTask);
                OnThresholdReached.Broadcast();
            }
        }).Share());
}


int USyncIntMethodHandler::getCount()
{
    return m_counter;
}

std::vector<chrono_hr_timepoint>& USyncIntMethodHandler::getStartPoints()
{
    return m_startTimePoints;
}

std::vector<chrono_hr_timepoint>& USyncIntMethodHandler::getStopPoints()
{
    return m_stopTimePoints;
}
