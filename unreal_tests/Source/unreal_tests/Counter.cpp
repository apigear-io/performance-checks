// Fill out your copyright notice in the Description page of Project Settings.


#include "Counter.h"

void UCounter::increaseInt(int notUsedPsrameter)
{
    counter+=1;
    if (counter >= Threshold)
    {
        std::cout << "Threshold reached" << std::endl;
        OnThresholdReached.Broadcast();
    }
}
    
void UCounter::increaseString(const FString& notUsedPsrameter)
{
    counter+=1;
    if (counter >= Threshold)
    {
        std::cout << "Threshold reached" << std::endl;
        OnThresholdReached.Broadcast();
    }
}
    
void UCounter::increaseFloat(const float notUsedPsrameter)
{
    counter++;
    if (counter >= Threshold)
    {
        OnThresholdReached.Broadcast();
    }
}
    
int UCounter::getCount()
{
    return counter;
}
