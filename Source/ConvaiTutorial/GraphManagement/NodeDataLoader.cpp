// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeDataLoader.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include <Kismet/GameplayStatics.h>
#include "Engine/World.h"
#include "Engine/Engine.h"




void UNodeDataLoader::SetWorld(UWorld* InWorld)
{
    World = InWorld;
}

// This function generates an array of subtopic names.
TArray<FString> UNodeDataLoader::GenerateSubtopicNames()
{
    TArray<FString> SubTopicNames;
    if (World)
    {        
        UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(World->GetGameInstance());

        if (GameInstance)
        {
            // First, flatten the structure into a list of subtopic names
            // Generate a list of subtopic names from the GameInstance.
            for (FSectionStruct& Section : GameInstance->SectionDataArray)
            {
                for (FTopic& Topic : Section.Topics)
                {
                    for (FSubtopic& SubTopic : Topic.Subtopics)
                    {
                        SubTopicNames.Add(SubTopic.Title);
                    }
                }
            }
        }
    }
    return SubTopicNames;
}


TArray<FString> UNodeDataLoader::GenerateSubtopicContents(const FSubjectStruct& CurrentSubject)
{
    TArray<FString> SubTopicContent;
    if (World)
    {
        UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(World->GetGameInstance());

        if (GameInstance)
        {
            // First, flatten the structure into a list of subtopic names
            // Generate a list of subtopic names from the GameInstance.
            for (const FSectionStruct& Section : CurrentSubject.SubjectDetailsArray)
            {
                for (const FTopic& Topic : Section.Topics)
                {
                    for (const FSubtopic& Subtopic : Topic.Subtopics)
                    {
                        SubTopicContent.Add(Subtopic.Content);

                    }
                }
            }
        }
    }
    return SubTopicContent;
}


