// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvaiTutorial/DataManagement/FieldDataManager.h"

#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"



void UFieldDataManager::RegisterObserver(UUserInteractionDataManager* observer)
{
    Observers.Add(observer);
}

void UFieldDataManager::UnregisterObserver(UUserInteractionDataManager* observer)
{
    Observers.Remove(observer);
}


void UFieldDataManager::AccessTopic(FName TopicName)
{
    // Find the topic that was accessed
    int32 TopicIndex = Topics.IndexOfByPredicate([&](const FTopicDataTestStruct& Topic) { return Topic.TopicName == TopicName; });

    if (TopicIndex != INDEX_NONE)
    {
        // Notify observers that the topic was accessed
        for (UUserInteractionDataManager* Observer : Observers)
        {
            Observer->UpdateAccess(TopicName);
        }
    }
}

void UFieldDataManager::AddTopic(FName TopicName)
{
    FTopicDataTestStruct NewTopic;
    NewTopic.TopicName = TopicName;
    Topics.Add(NewTopic);
}


