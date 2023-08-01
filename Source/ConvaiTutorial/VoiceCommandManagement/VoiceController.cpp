// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceController.h"

#include "ConvaiTutorial/BaseClasses/CoreGameMode.h"
#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"



FString UVoiceController::PrintContentForVoicePrompt(FString VoicePrompt)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("World is null in PrintContentForVoicePrompt"));
        return FString();
    }

    UGameInstance* GameInstanceTemp = World->GetGameInstance();
    if (!GameInstanceTemp)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameInstance is null in PrintContentForVoicePrompt"));
        return FString();
    }

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GameInstanceTemp);
    if (!GameInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("BaseGameInstance cast failed in PrintContentForVoicePrompt"));
        return FString();
    }

    // Traverse the field data array
    for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
    {
        // Traverse the areas within each field
        for (const FAreaStruct& AreaData : FieldData.Areas)
        {
            // Traverse the subject groups within each area
            for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
            {
                // Traverse the subjects within each subject group
                for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
                {
                    // Check if the subject's name matches the voice prompt
                    if (SubjectData.SubjectName.Contains(VoicePrompt, ESearchCase::IgnoreCase))
                    {
                        // // We've found the desired topic, now we can print its content
                        // if (GEngine)
                        // {
                        //     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Content function: %s"), *SubjectData.SubjectName));
                        // }
                        // if (UpdateTextWidget)
                        // {
                        //     UpdateTextWidget(SubjectData.SubjectName);
                        // }
                        // else
                        // {
                        //     UE_LOG(LogTemp, Warning, TEXT("UpdateTextWidget is null in PrintContentForVoicePrompt"));
                        // }

                        return SubjectData.SubjectName;
                    }
                }
            }
        }
    }

    // If we've gotten this far, the voice prompt did not match any subject
    UE_LOG(LogTemp, Warning, TEXT("No content found for voice prompt: %s"), *VoicePrompt);

    return FString();
}









FSubjectStruct UVoiceController::FindSubjectByVocalPrompt(FString SubjectName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance)
    {
        for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
        {
            for (const FAreaStruct& AreaData : FieldData.Areas)
            {
                for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
                {
                    for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
                    {
                        if (SubjectData.SubjectName.Contains(SubjectName, ESearchCase::IgnoreCase))
                        {
                            return SubjectData;
                        }
                    }
                }
            }
        }
    }
    return FSubjectStruct(); // Return an empty/default FSubjectStruct if no match found
}


void UVoiceController::RetrieveSectionsForSubject(FString SubjectName)
{
    // Retrieve the subject based on the SubjectName
    FSubjectStruct SubjectData = FindSubjectByVocalPrompt(SubjectName);

    // We no longer need the if (SubjectData) check here, because we're working with values directly,
    // not pointers. If there's no matching subject, SubjectData will be an empty/default FSubjectStruct.

    for (const FSectionStruct& Section : SubjectData.SubjectDetailsArray)
    {
        OnSectionFound(Section.SectionName);
        RetrieveTopicsForSection(Section);
    }
}

void UVoiceController::RetrieveTopicsForSection(const FSectionStruct& SectionData)
{
    for (const FTopic& Topic : SectionData.Topics)
    {
        OnTopicFound(Topic.Title);
        RetrieveSubtopicsForTopic(Topic);
    }
}

void UVoiceController::RetrieveSubtopicsForTopic(const FTopic& TopicData)
{
    for (const FSubtopic& Subtopic : TopicData.Subtopics)
    {
        OnSubtopicFound(Subtopic.Title);
    }
}


void UVoiceController::ClearContentForVoicePrompt(FString VoicePrompt)
{
    if (VoicePrompt.Contains("Clear", ESearchCase::IgnoreCase))
    {
        // pritn to screen that content is cleared
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Content cleared")));
        }
        OnClearContent();
    }
}

ACharacter* UVoiceController::GetPlayerCharacter()
{
    UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
    if (World)
    {
        return Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
    }
    return nullptr;
}