// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"
#include "ConvaiTutorial/DataManagement/FieldDataManager.h"



//void UUserInteractionDataManager::UpdateAccess(FName TopicName)
//{
//    // Find the corresponding user interaction
//    int32 InteractionIndex = UserInteractions.IndexOfByPredicate([&](const FUserInteractionData& Interaction) { return Interaction.TopicName == TopicName; });
//
//    if (InteractionIndex != INDEX_NONE)
//    {
//        // Increase the number of times the topic was accessed
//        UserInteractions[InteractionIndex].TimesAccessed++;
//    }
//}

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

        FAreaInteractionData* AreaInteractionData = FieldInteractionData->Areas.Find(AreaNameStr);

        if (AreaInteractionData)
        {
            AreaInteractionData->TimesAccessed++;

            FSubjectGroupInteractionData* SubjectGroupInteractionData = AreaInteractionData->SubjectGroups.Find(SubjectGroupNameStr);

            if (SubjectGroupInteractionData)
            {
                SubjectGroupInteractionData->TimesAccessed++;

                FSubjectInteractionData* SubjectInteractionData = SubjectGroupInteractionData->Subjects.Find(SubjectNameStr);

                if (SubjectInteractionData)
                {
                    SubjectInteractionData->TimesAccessed++;

                    FSectionInteractionData* SectionInteractionData = SubjectInteractionData->Sections.Find(SectionNameStr);

                    if (SectionInteractionData)
                    {
                        SectionInteractionData->TimesAccessed++;

                        FTopicInteractionData* TopicInteractionData = SectionInteractionData->Topics.Find(TopicNameStr);

                        if (TopicInteractionData)
                        {
                            // Increase the number of times the topic was accessed
                            TopicInteractionData->TimesAccessed++;
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