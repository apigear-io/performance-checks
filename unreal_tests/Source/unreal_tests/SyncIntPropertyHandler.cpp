// Fill out your copyright notice in the Description page of Project Settings.

#include "SyncIntPropertyHandler.h"



void USyncIntPropertyHandler::initialize(UApiTestApi0OLinkClient* clientApi0,
                int startValue,
                int messagesCount)
{
    Threshold = messagesCount;
    m_clientApi0= clientApi0;
    currentNumber = startValue +1;//Changes are not sent if request is for already set property. Default value for Int is "0", in test we always add 1 for setting int property to make sure value is always set.
    m_startTimePoints= std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
    m_stopTimePoints =  std::vector<chrono_hr_timepoint>(messagesCount, chrono_hr_timepoint());
    OnTaskEnded.AddDynamic(this, &USyncIntPropertyHandler::executeNextTask);
    m_clientApi0->_GetSignals_Implementation()->OnPropIntChanged.AddDynamic(this, &USyncIntPropertyHandler::onPropertyChangeReceived);
}

void USyncIntPropertyHandler::onPropertyChangeReceived(int number)
{
    if (number == currentNumber)
    {
        m_stopTimePoints[counter] = std::chrono::high_resolution_clock::now();
        counter+=1;
        currentNumber+=1;
    }
    else { return; }

    if (counter == Threshold)
    {
        OnTaskEnded.RemoveDynamic(this, &USyncIntPropertyHandler::executeNextTask);
        OnThresholdReached.Broadcast();
    }
    else 
    {
        OnTaskEnded.Broadcast();
    }
}

void USyncIntPropertyHandler::executeNextTask()
{
    m_startTimePoints[counter] = std::chrono::high_resolution_clock::now();
    m_clientApi0->Execute_SetPropInt(m_clientApi0, currentNumber);
}

int USyncIntPropertyHandler::getCount()
{
    return counter;
}


std::vector<chrono_hr_timepoint>& USyncIntPropertyHandler::getStartPoints()
{
    return m_startTimePoints;
}

std::vector<chrono_hr_timepoint>& USyncIntPropertyHandler::getStopPoints()
{
    return m_stopTimePoints;
}

