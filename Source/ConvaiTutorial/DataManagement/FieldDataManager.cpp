// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvaiTutorial/DataManagement/FieldDataManager.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"



void UFieldDataManager::RegisterObserver(UUserInteractionDataManager* observer)
{
    Observers.Add(observer);
}

void UFieldDataManager::UnregisterObserver(UUserInteractionDataManager* observer)
{
    Observers.Remove(observer);
}



void UFieldDataManager::AccessTopic(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName)
{
    int32 FieldIndex = GetFieldIndex(FieldName);
    int32 AreaIndex = GetAreaIndex(FieldIndex, AreaName);
    int32 SubjectGroupIndex = GetSubjectGroupIndex(FieldIndex, AreaIndex, SubjectGroupName);
    int32 SubjectIndex = GetSubjectIndex(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectName);
    int32 SectionIndex = GetSectionIndex(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectIndex, SectionName);

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());


    if (SectionIndex != INDEX_NONE)
    {
        // Find the topic that was accessed
        int32 TopicIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectDetailsArray[SectionIndex].Topics.IndexOfByPredicate([&](const FTopic& Topic) { return Topic.Title == TopicName.ToString(); });
        UE_LOG(LogTemp, Warning, TEXT("Accessing topic: %s"), *TopicName.ToString());

        if (TopicIndex != INDEX_NONE)
        {
            // Notify observers that the topic was accessed
            for (UUserInteractionDataManager* Observer : Observers)
            {
                Observer->UpdateAccess(FieldName, AreaName, SubjectGroupName, SubjectName, SectionName, TopicName);
            }
        }
    }

}



/**
void UFieldDataManager::AccessSection(FName SectionName)

 * @brief This function is used to access a section in the game. It updates the UserInteractionDataManager with the details of the accessed section.
 *
 * @param SectionName The name of the section that is being accessed.
 *
 * @return void This function does not return a value. It's purpose is to update the UserInteractionDataManager with the details of the accessed section.
 *
 * @note This function refers to the UBaseGameInstance, UUserInteractionDataManager classes and the UpdateAccess function in the UUserInteractionDataManager class.
 *
 * The function does the following:
 * - It gets a reference to the GameInstance.
 * - It iterates over the FieldDataArray in the GameInstance.
 * - For each field, it iterates over the Areas.
 * - For each area, it iterates over the SubjectGroups.
 * - For each subject group, it iterates over the Subjects.
 * - It checks if the section name matches the input section name.
 * - If a match is found, it notifies all observers (UserInteractionDataManagers) and updates them with the details of the accessed section.
 *
 * This function makes use of several basic coding principles including:
 * - Loops for iteration over arrays
 * - Conditional statements for checking equality
 * - Use of observer pattern for updating observers
 *
 * @warning The function assumes that the SectionName provided is valid and exists within the game's data structure. It does not handle the case where a section with the provided name does not exist.
 */

void UFieldDataManager::AccessSection(FName SectionName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    for (int32 FieldIndex = 0; FieldIndex < GameInstance->FieldDataArray.Num(); ++FieldIndex)
    {
        for (int32 AreaIndex = 0; AreaIndex < GameInstance->FieldDataArray[FieldIndex].Areas.Num(); ++AreaIndex)
        {
            for (int32 SubjectGroupIndex = 0; SubjectGroupIndex < GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups.Num(); ++SubjectGroupIndex)
            {
                for (int32 SubjectIndex = 0; SubjectIndex < GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects.Num(); ++SubjectIndex)
                {
                    // Find the section that was accessed
                    int32 SectionIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectDetailsArray.IndexOfByPredicate([&](const FSectionStruct& Section) { return Section.SectionName == SectionName.ToString(); });

                    if (SectionIndex != INDEX_NONE)
                    {
                        // Notify observers that the section was accessed
                        for (UUserInteractionDataManager* Observer : Observers)
                        {
                            Observer->UpdateAccess(
                                FName(GameInstance->FieldDataArray[FieldIndex].FieldName),
                                FName(GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].AreaName),
                                FName(GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].SubjectGroupName),
                                FName(GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectName),
                                SectionName
                            );
                        }
                    }
                }
            }
        }
    }
}



void UFieldDataManager::AccessSubject(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName)
{
    int32 FieldIndex = GetFieldIndex(FieldName);
    int32 AreaIndex = GetAreaIndex(FieldIndex, AreaName);
    int32 SubjectGroupIndex = GetSubjectGroupIndex(FieldIndex, AreaIndex, SubjectGroupName);

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());


    if (SubjectGroupIndex != INDEX_NONE)
    {
        // Find the subject that was accessed
        int32 SubjectIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects.IndexOfByPredicate([&](const FSubjectStruct& Subject) { return Subject.SubjectName == SubjectName.ToString(); });

        if (SubjectIndex != INDEX_NONE)
        {
            // Notify observers that the subject was accessed
            for (UUserInteractionDataManager* Observer : Observers)
            {
                Observer->UpdateAccess(FieldName, AreaName, SubjectGroupName, SubjectName);
            }
        }
    }
}

void UFieldDataManager::AccessSubjectGroup(FName FieldName, FName AreaName, FName SubjectGroupName)
{
    int32 FieldIndex = GetFieldIndex(FieldName);
    int32 AreaIndex = GetAreaIndex(FieldIndex, AreaName);

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    if (AreaIndex != INDEX_NONE)
    {
        // Find the subject group that was accessed
        int32 SubjectGroupIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups.IndexOfByPredicate([&](const FSubjectGroupStruct& SubjectGroup) { return SubjectGroup.SubjectGroupName == SubjectGroupName.ToString(); });

        if (SubjectGroupIndex != INDEX_NONE)
        {
            // Notify observers that the subject group was accessed
            for (UUserInteractionDataManager* Observer : Observers)
            {
                Observer->UpdateAccess(FieldName, AreaName, SubjectGroupName);
            }
        }
    }
}

void UFieldDataManager::AccessArea(FName FieldName, FName AreaName)
{
    int32 FieldIndex = GetFieldIndex(FieldName);

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    if (FieldIndex != INDEX_NONE)
    {
        // Find the area that was accessed
        int32 AreaIndex = GameInstance->FieldDataArray[FieldIndex].Areas.IndexOfByPredicate([&](const FAreaStruct& Area) { return Area.AreaName == AreaName.ToString(); });

        if (AreaIndex != INDEX_NONE)
        {
            // Notify observers that the area was accessed
            for (UUserInteractionDataManager* Observer : Observers)
            {
                Observer->UpdateAccess(FieldName, AreaName);
            }
        }
    }
}

void UFieldDataManager::AccessField(FName FieldName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    // Find the field that was accessed
    int32 FieldIndex = GameInstance->FieldDataArray.IndexOfByPredicate([&](const FFieldStruct& Field) { return Field.FieldName == FieldName.ToString(); });


    if (FieldIndex != INDEX_NONE)
    {
        // Notify observers that the field was accessed
        for (UUserInteractionDataManager* Observer : Observers)
        {
            Observer->UpdateAccess(FieldName);
        }
    }
}


//void UFieldDataManager::AccessSection(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName)
//{
//    // Get the game instance
//    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
//
//    if (GameInstance)
//    {
//        // Find the field that was accessed
//        int32 FieldIndex = GameInstance->FieldDataArray.IndexOfByPredicate([&](const FFieldStruct& Field) { return Field.FieldName == FieldName.ToString(); });
//
//        if (FieldIndex != INDEX_NONE)
//        {
//            // Find the area that was accessed
//            int32 AreaIndex = GameInstance->FieldDataArray[FieldIndex].Areas.IndexOfByPredicate([&](const FAreaStruct& Area) { return Area.AreaName == AreaName.ToString(); });
//
//            if (AreaIndex != INDEX_NONE)
//            {
//                // Find the subject group that was accessed
//                int32 SubjectGroupIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups.IndexOfByPredicate([&](const FSubjectGroupStruct& SubjectGroup) { return SubjectGroup.SubjectGroupName == SubjectGroupName.ToString(); });
//
//                if (SubjectGroupIndex != INDEX_NONE)
//                {
//                    // Find the subject that was accessed
//                    int32 SubjectIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects.IndexOfByPredicate([&](const FSubjectStruct& Subject) { return Subject.SubjectName == SubjectName.ToString(); });
//
//                    if (SubjectIndex != INDEX_NONE)
//                    {
//                        // Find the section that was accessed
//                        int32 SectionIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectDetailsArray.IndexOfByPredicate([&](const FSectionStruct& Section) { return Section.SectionName == SectionName.ToString(); });
//
//                        if (SectionIndex != INDEX_NONE)
//                        {
//                            // Notify observers that the section was accessed
//                            for (UUserInteractionDataManager* Observer : Observers)
//                            {
//                                Observer->UpdateAccess(FieldName, AreaName, SubjectGroupName, SubjectName, SectionName);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//}

//void UFieldDataManager::AccessTopic(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName)
//{
//    // Get the game instance
//    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
//
//    if (GameInstance)
//    {
//        // Find the field that was accessed
//        int32 FieldIndex = GameInstance->FieldDataArray.IndexOfByPredicate([&](const FFieldStruct& Field) { return Field.FieldName == FieldName.ToString(); });
//
//        if (FieldIndex != INDEX_NONE)
//        {
//            // Find the area that was accessed
//            int32 AreaIndex = GameInstance->FieldDataArray[FieldIndex].Areas.IndexOfByPredicate([&](const FAreaStruct& Area) { return Area.AreaName == AreaName.ToString(); });
//
//            if (AreaIndex != INDEX_NONE)
//            {
//                // Find the subject group that was accessed
//                int32 SubjectGroupIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups.IndexOfByPredicate([&](const FSubjectGroupStruct& SubjectGroup) { return SubjectGroup.SubjectGroupName == SubjectGroupName.ToString(); });
//
//                if (SubjectGroupIndex != INDEX_NONE)
//                {
//                    // Find the subject that was accessed
//                    int32 SubjectIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects.IndexOfByPredicate([&](const FSubjectStruct& Subject) { return Subject.SubjectName == SubjectName.ToString(); });
//
//                    if (SubjectIndex != INDEX_NONE)
//                    {
//                        // Find the section that was accessed
//                        int32 SectionIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectDetailsArray.IndexOfByPredicate([&](const FSectionStruct& Section) { return Section.SectionName == SectionName.ToString(); });
//
//                        if (SectionIndex != INDEX_NONE)
//                        {
//                            // Find the topic that was accessed
//                            int32 TopicIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectDetailsArray[SectionIndex].Topics.IndexOfByPredicate([&](const FTopic& Topic) { return Topic.Title == TopicName.ToString(); });
//
//                            if (TopicIndex != INDEX_NONE)
//                            {
//                                // Notify observers that the topic was accessed
//                                for (UUserInteractionDataManager* Observer : Observers)
//                                {
//                                    Observer->UpdateAccess(FieldName, AreaName, SubjectGroupName, SubjectName, SectionName, TopicName);
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//}




int32 UFieldDataManager::GetFieldIndex(FName FieldName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        return GameInstance->FieldDataArray.IndexOfByPredicate([&](const FFieldStruct& Field) { return Field.FieldName == FieldName.ToString(); });
    }

    return INDEX_NONE;
}

int32 UFieldDataManager::GetAreaIndex(int32 FieldIndex, FName AreaName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    if (FieldIndex != INDEX_NONE)
    {
        return GameInstance->FieldDataArray[FieldIndex].Areas.IndexOfByPredicate([&](const FAreaStruct& Area) { return Area.AreaName == AreaName.ToString(); });
    }

    return INDEX_NONE;
}

int32 UFieldDataManager::GetSubjectGroupIndex(int32 FieldIndex, int32 AreaIndex, FName SubjectGroupName)
{
    if (FieldIndex != INDEX_NONE && AreaIndex != INDEX_NONE)
    {
        UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

        if (GameInstance)
        {
            return GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups.IndexOfByPredicate([&](const FSubjectGroupStruct& SubjectGroup) { return SubjectGroup.SubjectGroupName == SubjectGroupName.ToString(); });
        }
    }

    return INDEX_NONE;
}

int32 UFieldDataManager::GetSubjectIndex(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, FName SubjectName)
{
    if (FieldIndex != INDEX_NONE && AreaIndex != INDEX_NONE && SubjectGroupIndex != INDEX_NONE)
    {
        UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

        if (GameInstance)
        {
            return GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects.IndexOfByPredicate([&](const FSubjectStruct& Subject) { return Subject.SubjectName == SubjectName.ToString(); });
        }
    }

    return INDEX_NONE;
}

int32 UFieldDataManager::GetSectionIndex(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, FName SectionName)
{
    if (FieldIndex != INDEX_NONE && AreaIndex != INDEX_NONE && SubjectGroupIndex != INDEX_NONE && SubjectIndex != INDEX_NONE)
    {
        UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

        if (GameInstance)
        {
            return GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectDetailsArray.IndexOfByPredicate([&](const FSectionStruct& Section) { return Section.SectionName == SectionName.ToString(); });
        }
    }

    return INDEX_NONE;
}





void UFieldDataManager::AddTopic(FName TopicName)
{
    FTopicDataTestStruct NewTopic;
    NewTopic.TopicName = TopicName;
    Topics.Add(NewTopic);
}


FString UFieldDataManager::ToString() const
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    return FString::Printf(TEXT("Number of Fields: %d"), GameInstance->FieldDataArray.Num());
}