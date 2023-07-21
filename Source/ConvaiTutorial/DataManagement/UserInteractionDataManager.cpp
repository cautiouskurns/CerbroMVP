// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"



void UUserInteractionDataManager::UpdateAccess(FName TopicName)
{
    // Find the corresponding user interaction
    int32 InteractionIndex = UserInteractions.IndexOfByPredicate([&](const FUserInteractionStruct& Interaction) { return Interaction.TopicName == TopicName; });

    if (InteractionIndex != INDEX_NONE)
    {
        // Increase the number of times the topic was accessed
        UserInteractions[InteractionIndex].TimesAccessed++;
    }
}

int32 UUserInteractionDataManager::GetTimesAccessed(FName TopicName)
{
    // Find the corresponding user interaction
    int32 InteractionIndex = UserInteractions.IndexOfByPredicate([&](const FUserInteractionStruct& Interaction) { return Interaction.TopicName == TopicName; });

    if (InteractionIndex != INDEX_NONE)
    {
        // Return the number of times the topic was accessed
        return UserInteractions[InteractionIndex].TimesAccessed;
    }

    // If the topic was not found, return -1 or some other invalid value
    return -1;
}

void UUserInteractionDataManager::AddInteraction(FName TopicName)
{
    FUserInteractionStruct NewInteraction;
    NewInteraction.TopicName = TopicName;
    NewInteraction.TimesAccessed = 0;

    UserInteractions.Add(NewInteraction);
}
