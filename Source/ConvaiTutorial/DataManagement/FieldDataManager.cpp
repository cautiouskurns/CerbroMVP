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


void UFieldDataManager::AccessSection(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName)
{
    int32 FieldIndex = GetFieldIndex(FieldName);
    int32 AreaIndex = GetAreaIndex(FieldIndex, AreaName);
    int32 SubjectGroupIndex = GetSubjectGroupIndex(FieldIndex, AreaIndex, SubjectGroupName);
    int32 SubjectIndex = GetSubjectIndex(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectName);

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());


    if (SubjectIndex != INDEX_NONE)
    {
        // Find the section that was accessed
        int32 SectionIndex = GameInstance->FieldDataArray[FieldIndex].Areas[AreaIndex].SubjectGroups[SubjectGroupIndex].Subjects[SubjectIndex].SubjectDetailsArray.IndexOfByPredicate([&](const FSectionStruct& Section) { return Section.SectionName == SectionName.ToString(); });

        if (SectionIndex != INDEX_NONE)
        {
            // Notify observers that the section was accessed
            for (UUserInteractionDataManager* Observer : Observers)
            {
                Observer->UpdateAccess(FieldName, AreaName, SubjectGroupName, SubjectName, SectionName);
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


