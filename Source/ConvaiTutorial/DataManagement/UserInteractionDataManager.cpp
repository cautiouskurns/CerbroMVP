// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"

#include <ConvaiTutorial/BaseClasses/BaseGameInstance.h>

#include "ConvaiTutorial/DataManagement/FieldDataManager.h"



void UUserInteractionDataManager::UpdateAccess(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName)
{
    // Convert the FNames to FStrings
    FString FieldNameStr = FieldName.ToString();
    FString AreaNameStr = AreaName.ToString();
    FString SubjectGroupNameStr = SubjectGroupName.ToString();
    FString SubjectNameStr = SubjectName.ToString();
    FString SectionNameStr = SectionName.ToString();
    FString TopicNameStr = TopicName.ToString();

    // Find the corresponding user interaction
    FFieldInteractionData* FieldInteractionData = UserInteractions.Fields.Find(FieldNameStr);

    if (FieldInteractionData)
    {
        FieldInteractionData->TimesAccessed++;
        FieldInteractionData->LastAccessedTime = FDateTime::UtcNow();

        FAreaInteractionData* AreaInteractionData = FieldInteractionData->Areas.Find(AreaNameStr);

        if (AreaInteractionData)
        {
            AreaInteractionData->TimesAccessed++;
            AreaInteractionData->LastAccessedTime = FDateTime::UtcNow();

            FSubjectGroupInteractionData* SubjectGroupInteractionData = AreaInteractionData->SubjectGroups.Find(SubjectGroupNameStr);

            if (SubjectGroupInteractionData)
            {
                SubjectGroupInteractionData->TimesAccessed++;
                SubjectGroupInteractionData->LastAccessedTime = FDateTime::UtcNow();

                FSubjectInteractionData* SubjectInteractionData = SubjectGroupInteractionData->Subjects.Find(SubjectNameStr);

                if (SubjectInteractionData)
                {
                    SubjectInteractionData->TimesAccessed++;
                    SubjectInteractionData->LastAccessedTime = FDateTime::UtcNow();

                    FSectionInteractionData* SectionInteractionData = SubjectInteractionData->Sections.Find(SectionNameStr);

                    if (SectionInteractionData)
                    {
                        SectionInteractionData->TimesAccessed++;
                        SectionInteractionData->LastAccessedTime = FDateTime::UtcNow();

                        FTopicInteractionData* TopicInteractionData = SectionInteractionData->Topics.Find(TopicNameStr);

                        if (TopicInteractionData)
                        {
                            // Increase the number of times the topic was accessed
                            TopicInteractionData->TimesAccessed++;
                            TopicInteractionData->LastAccessedTime = FDateTime::UtcNow();

                            //UE_LOG(LogTemp, Warning, TEXT("Updated access for topic: %s. New count: %d"), *TopicName.ToString(), TopicInteractionData->TimesAccessed);

                        }
                    }
                }
            }
        }
    }


}

void UUserInteractionDataManager::UpdateQuestionInteractionData(FString FieldName, FString AreaName, FString SubjectGroupName, FString SubjectName, FString SectionName, FString TopicName, FString SubtopicName, FString QuestionText, bool IsAnswerCorrect)
{
    // Convert the FNames to FStrings
    FString FieldNameStr = FieldName;
    FString AreaNameStr = AreaName;
    FString SubjectGroupNameStr = SubjectGroupName;
    FString SubjectNameStr = SubjectName;
    FString SectionNameStr = SectionName;
    FString TopicNameStr = TopicName;
    FString SubtopicNameStr = SubtopicName;

    // Find the corresponding user interaction
    FFieldInteractionData* FieldInteractionData = UserInteractions.Fields.Find(FieldNameStr);

    if (FieldInteractionData)
    {
        if (FieldInteractionData)
        {
            FAreaInteractionData* AreaInteractionData = FieldInteractionData->Areas.Find(AreaNameStr);

            if (AreaInteractionData)
            {
                FSubjectGroupInteractionData* SubjectGroupInteractionData = AreaInteractionData->SubjectGroups.Find(SubjectGroupNameStr);

                if (SubjectGroupInteractionData)
                {
                    FSubjectInteractionData* SubjectInteractionData = SubjectGroupInteractionData->Subjects.Find(SubjectNameStr);

                    if (SubjectInteractionData)
                    {
                        FSectionInteractionData* SectionInteractionData = SubjectInteractionData->Sections.Find(SectionNameStr);

                        if (SectionInteractionData)
                        {
                            FTopicInteractionData* TopicInteractionData = SectionInteractionData->Topics.Find(TopicNameStr);

                            if (TopicInteractionData)
                            {
                                FSubtopicInteractionData* SubtopicInteractionData = TopicInteractionData->Subtopics.Find(SubtopicNameStr);

                                if (SubtopicInteractionData)
                                {
                                    FQuestionInteractionData* QuestionInteractionData = SubtopicInteractionData->Questions.Find(QuestionText);

                                    if (QuestionInteractionData)
                                    {
                                        // Increase the number of times the question was asked
                                        QuestionInteractionData->TimesAsked++;

                                        UE_LOG(LogTemp, Warning, TEXT("Updating question interaction data for question: %s. New TimesTested count: %d"), *QuestionText, QuestionInteractionData->TimesAsked);


                                        if (IsAnswerCorrect)
                                        {
                                            // Increase the number of times the question was answered correctly
                                            QuestionInteractionData->TimesCorrect++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        // Log an error message or handle the error as appropriate for your application
        UE_LOG(LogTemp, Warning, TEXT("Field not found: %s"), *FieldNameStr);
    }


   
}

int32 UUserInteractionDataManager::GetTimesAccessed(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName)
{
    // Convert the FNames to FStrings
    FString FieldNameStr = FieldName.ToString();
    FString AreaNameStr = AreaName.ToString();
    FString SubjectGroupNameStr = SubjectGroupName.ToString();
    FString SubjectNameStr = SubjectName.ToString();
    FString SectionNameStr = SectionName.ToString();
    FString TopicNameStr = TopicName.ToString();

    // Find the corresponding user interaction
    FFieldInteractionData* FieldInteractionData = UserInteractions.Fields.Find(FieldNameStr);

    if (FieldInteractionData)
    {
        FAreaInteractionData* AreaInteractionData = FieldInteractionData->Areas.Find(AreaNameStr);

        if (AreaInteractionData)
        {
            FSubjectGroupInteractionData* SubjectGroupInteractionData = AreaInteractionData->SubjectGroups.Find(SubjectGroupNameStr);

            if (SubjectGroupInteractionData)
            {
                FSubjectInteractionData* SubjectInteractionData = SubjectGroupInteractionData->Subjects.Find(SubjectNameStr);

                if (SubjectInteractionData)
                {
                    FSectionInteractionData* SectionInteractionData = SubjectInteractionData->Sections.Find(SectionNameStr);

                    if (SectionInteractionData)
                    {
                        FTopicInteractionData* TopicInteractionData = SectionInteractionData->Topics.Find(TopicNameStr);

                        if (TopicInteractionData)
                        {
                            // Return the number of times the topic was accessed
                            return TopicInteractionData->TimesAccessed;
                        }
                    }
                }
            }
        }
    }

    // If the topic was not found, return -1 or some other invalid value
    return -1;
}



void UUserInteractionDataManager::AddInteraction(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName)
{
    // Find or add the field interaction data
    FFieldInteractionData& FieldInteractionData = UserInteractions.Fields.FindOrAdd(FieldName.ToString());

    // Find or add the area interaction data
    FAreaInteractionData& AreaInteractionData = FieldInteractionData.Areas.FindOrAdd(AreaName.ToString());

    // Find or add the subject group interaction data
    FSubjectGroupInteractionData& SubjectGroupInteractionData = AreaInteractionData.SubjectGroups.FindOrAdd(SubjectGroupName.ToString());

    // Find or add the subject interaction data
    FSubjectInteractionData& SubjectInteractionData = SubjectGroupInteractionData.Subjects.FindOrAdd(SubjectName.ToString());

    // Find or add the section interaction data
    FSectionInteractionData& SectionInteractionData = SubjectInteractionData.Sections.FindOrAdd(SectionName.ToString());

    // Find or add the topic interaction data
    FTopicInteractionData& TopicInteractionData = SectionInteractionData.Topics.FindOrAdd(TopicName.ToString());

    // Initialize the interaction data for the topic
    TopicInteractionData.TimesAccessed = 0;
    TopicInteractionData.ProficiencyScore = 0.0f;
    TopicInteractionData.LastInteractionDuration = 0.0f;
    TopicInteractionData.AverageInteractionDuration = 0.0f;
}


void UUserInteractionDataManager::InitializeUserInteractions(const TArray<FFieldStruct>& FieldDataArray)
{
    // Clear any existing interactions
    UserInteractions.Fields.Empty();

    // Iterate over the FieldDataArray
    for (const FFieldStruct& Field : FieldDataArray)
    {
        // Create a new FFieldInteractionData for this field
        FFieldInteractionData FieldInteractionData;
        InitializeField(Field, FieldInteractionData);

        // Add the FFieldInteractionData to the UserInteractions.Fields map
        UserInteractions.Fields.Add(Field.FieldName, FieldInteractionData);
    }
}

void UUserInteractionDataManager::InitializeField(const FFieldStruct& Field, FFieldInteractionData& FieldInteractionData)
{
    // Initialize the data for this field
    // (you might want to add more initialization code here as needed)
    FieldInteractionData.TimesAccessed = 0;
    FieldInteractionData.ProficiencyScore = 0.0f;
    FieldInteractionData.LastInteractionDuration = 0.0f;
    FieldInteractionData.AverageInteractionDuration = 0.0f;

    for (const FAreaStruct& Area : Field.Areas)
    {
        FAreaInteractionData AreaInteractionData;
        InitializeArea(Area, AreaInteractionData);

        FieldInteractionData.Areas.Add(Area.AreaName, AreaInteractionData);
    }
}

void UUserInteractionDataManager::InitializeArea(const FAreaStruct& Area, FAreaInteractionData& AreaInteractionData)
{
    // Initialize the data for this area
    // (you might want to add more initialization code here as needed)
    AreaInteractionData.TimesAccessed = 0;
    AreaInteractionData.ProficiencyScore = 0.0f;
    AreaInteractionData.LastInteractionDuration = 0.0f;
    AreaInteractionData.AverageInteractionDuration = 0.0f;

    for (const FSubjectGroupStruct& SubjectGroup : Area.SubjectGroups)
    {
        FSubjectGroupInteractionData SubjectGroupInteractionData;
        InitializeSubjectGroup(SubjectGroup, SubjectGroupInteractionData);

        AreaInteractionData.SubjectGroups.Add(SubjectGroup.SubjectGroupName, SubjectGroupInteractionData);
    }
}

void UUserInteractionDataManager::InitializeSubjectGroup(const FSubjectGroupStruct& SubjectGroup, FSubjectGroupInteractionData& SubjectGroupInteractionData)
{
    // Initialize the data for this subject group
    // (you might want to add more initialization code here as needed)
    SubjectGroupInteractionData.TimesAccessed = 0;
    SubjectGroupInteractionData.ProficiencyScore = 0.0f;
    SubjectGroupInteractionData.LastInteractionDuration = 0.0f;
    SubjectGroupInteractionData.AverageInteractionDuration = 0.0f;

    for (const FSubjectStruct& Subject : SubjectGroup.Subjects)
    {
        FSubjectInteractionData SubjectInteractionData;
        InitializeSubject(Subject, SubjectInteractionData);

        SubjectGroupInteractionData.Subjects.Add(Subject.SubjectName, SubjectInteractionData);
    }
}

void UUserInteractionDataManager::InitializeSubject(const FSubjectStruct& Subject, FSubjectInteractionData& SubjectInteractionData)
{
    // Initialize the data for this subject
    // (you might want to add more initialization code here as needed)
    SubjectInteractionData.TimesAccessed = 0;
    SubjectInteractionData.ProficiencyScore = 0.0f;
    SubjectInteractionData.LastInteractionDuration = 0.0f;
    SubjectInteractionData.AverageInteractionDuration = 0.0f;

    for (const FSectionStruct& Section : Subject.SubjectDetailsArray)
    {
        FSectionInteractionData SectionInteractionData;
        InitializeSection(Section, SectionInteractionData);

        SubjectInteractionData.Sections.Add(Section.SectionName, SectionInteractionData);
    }
}

void UUserInteractionDataManager::InitializeSection(const FSectionStruct& Section, FSectionInteractionData& SectionInteractionData)
{
    // Initialize the data for this section
    // (you might want to add more initialization code here as needed)
    SectionInteractionData.TimesAccessed = 0;
    SectionInteractionData.ProficiencyScore = 0.0f;
    SectionInteractionData.LastInteractionDuration = 0.0f;
    SectionInteractionData.AverageInteractionDuration = 0.0f;

    for (const FTopic& Topic : Section.Topics)
    {
        FTopicInteractionData TopicInteractionData;
        InitializeTopic(Topic, TopicInteractionData);

        SectionInteractionData.Topics.Add(Topic.Title, TopicInteractionData);
    }
}

void UUserInteractionDataManager::InitializeTopic(const FTopic& Topic, FTopicInteractionData& TopicInteractionData)
{
    // Initialize the data for this topic
    // (you might want to add more initialization code here as needed)
    TopicInteractionData.TimesAccessed = 0;
    TopicInteractionData.ProficiencyScore = 0.0f;
    TopicInteractionData.LastInteractionDuration = 0.0f;
    TopicInteractionData.AverageInteractionDuration = 0.0f;

    for (const FSubtopic& Subtopic : Topic.Subtopics)
    {
        FSubtopicInteractionData SubtopicInteractionData;
        InitializeSubtopic(Subtopic, SubtopicInteractionData);

        TopicInteractionData.Subtopics.Add(Subtopic.Title, SubtopicInteractionData);
    }
}

void UUserInteractionDataManager::InitializeSubtopic(const FSubtopic& Subtopic, FSubtopicInteractionData& SubtopicInteractionData)
{
    // Initialize the data for this subtopic
    // (you might want to add more initialization code here as needed)
    SubtopicInteractionData.TimesAccessed = 0;
    SubtopicInteractionData.ProficiencyScore = 0.0f;
    SubtopicInteractionData.LastInteractionDuration = 0.0f;
    SubtopicInteractionData.AverageInteractionDuration = 0.0f;

    for (const FTest& Question : Subtopic.Questions)
    {
        FQuestionInteractionData QuestionInteractionData;
        InitializeQuestion(Question, QuestionInteractionData);

        SubtopicInteractionData.Questions.Add(Question.Question, QuestionInteractionData);
    }
}

void UUserInteractionDataManager::InitializeQuestion(const FTest& Question, FQuestionInteractionData& QuestionInteractionData)
{
    // Initialize the data for this question
    // (you might want to add more initialization code here as needed)
    QuestionInteractionData.TimesAsked = 0;
    QuestionInteractionData.TimesCorrect = 0;
    QuestionInteractionData.TimesInCorrect = 0;
    QuestionInteractionData.ProficiencyScore = 0.0f;
    QuestionInteractionData.LastInteractionDuration = 0.0f;
    QuestionInteractionData.AverageInteractionDuration = 0.0f;
}


FString UUserInteractionDataManager::ToString() const
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());

    return FString::Printf(TEXT("Number of Fields: %d"), GameInstance->FieldDataArray.Num());
}


//FQuestionInteractionData UUserInteractionDataManager::GetQuestionInteractionData(const FString& QuestionText)
//{
//    // Loop over all fields
//    for (const auto& FieldPair : UserInteractions.Fields)
//    {
//        const FFieldInteractionData& FieldData = FieldPair.Value;
//
//        // Loop over all areas within the field
//        for (const auto& AreaPair : FieldData.Areas)
//        {
//            const FAreaInteractionData& AreaData = AreaPair.Value;
//
//            // Loop over all subject groups within the area
//            for (const auto& SubjectGroupPair : AreaData.SubjectGroups)
//            {
//                const FSubjectGroupInteractionData& SubjectGroupData = SubjectGroupPair.Value;
//
//                // Loop over all subjects within the subject group
//                for (const auto& SubjectPair : SubjectGroupData.Subjects)
//                {
//                    const FSubjectInteractionData& SubjectData = SubjectPair.Value;
//
//                    // Loop over all sections within the subject
//                    for (const auto& SectionPair : SubjectData.Sections)
//                    {
//                        const FSectionInteractionData& SectionData = SectionPair.Value;
//
//                        // Loop over all topics within the section
//                        for (const auto& TopicPair : SectionData.Topics)
//                        {
//                            const FTopicInteractionData& TopicData = TopicPair.Value;
//
//                            // Loop over all subtopics within the topic
//                            for (const auto& SubtopicPair : TopicData.Subtopics)
//                            {
//                                const FSubtopicInteractionData& SubtopicData = SubtopicPair.Value;
//
//                                // Look for the question within the subtopic
//                                const FQuestionInteractionData* QuestionData = SubtopicData.Questions.Find(QuestionText);
//
//                                if (QuestionData)
//                                {
//                                    // We found the question, so return the associated interaction data
//                                    return *QuestionData;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // If we reach this point, it means we couldn't find the question
//    // So we return an empty FQuestionInteractionData object
//    return FQuestionInteractionData();
//}


void UUserInteractionDataManager::SetUserInteractions(const FUserInteractionData& NewUserInteractions)
{
    UserInteractions = NewUserInteractions;
}

const FUserInteractionData& UUserInteractionDataManager::GetUserInteractions() const
{
    return UserInteractions;
}

const FFieldInteractionData* UUserInteractionDataManager::GetFieldInteractionData(const FString& FieldName) const
{
    return UserInteractions.Fields.Find(FieldName);
}

const FAreaInteractionData* UUserInteractionDataManager::GetAreaInteractionData(const FString& AreaName, const FFieldInteractionData& FieldData) const
{
    return FieldData.Areas.Find(AreaName);
}

const FSubjectGroupInteractionData* UUserInteractionDataManager::GetSubjectGroupInteractionData(const FString& SubjectGroupName, const FAreaInteractionData& AreaData) const
{
    return AreaData.SubjectGroups.Find(SubjectGroupName);
}

const FSubjectInteractionData* UUserInteractionDataManager::GetSubjectInteractionData(const FString& SubjectName, const FSubjectGroupInteractionData& SubjectGroupData) const
{
	return SubjectGroupData.Subjects.Find(SubjectName);
}


const FSectionInteractionData* UUserInteractionDataManager::GetSectionInteractionData(const FString& SectionName, const FSubjectInteractionData& SubjectData) const
{
	return SubjectData.Sections.Find(SectionName);
}

const FTopicInteractionData* UUserInteractionDataManager::GetTopicInteractionData(const FString& TopicName, const FSectionInteractionData& SectionData) const
{
	return SectionData.Topics.Find(TopicName);
}


const FSubtopicInteractionData* UUserInteractionDataManager::GetSubtopicInteractionData(const FString& SubtopicName, const FTopicInteractionData& TopicData) const
{
	return TopicData.Subtopics.Find(SubtopicName);
}

const FQuestionInteractionData* UUserInteractionDataManager::GetQuestionInteractionData(const FString& QuestionText, const FSubtopicInteractionData& SubtopicData) const
{
    return SubtopicData.Questions.Find(QuestionText);
}



int32 UUserInteractionDataManager::CalculateTimesAskedForSubtopic(const FString& SubtopicName, const FTopicInteractionData& TopicData)
{
    const FSubtopicInteractionData* SubtopicData = GetSubtopicInteractionData(SubtopicName, TopicData);
    if (!SubtopicData) return 0;

    int32 TotalTimesAsked = 0;
    for (const auto& QuestionPair : SubtopicData->Questions) {
        TotalTimesAsked += QuestionPair.Value.TimesAsked;
    }

    return TotalTimesAsked;
}