// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentRecommendationManager.h"
#include <ConvaiTutorial/MetricHandling/AssessmentMetricsCalculator.h>
#include <ConvaiTutorial/DataManagement/UserInteractionDataManager.h>

//UContentRecommendationManager::ContentRecommendationManager(); // UObject* ObjectInitializer, UUserInteractionDataManager* manager)
//{
//    //UserInteractionDataManager = manager;
//}

float UContentRecommendationManager::CalculateRecommendationScore(const FTopicInteractionData& TopicInteractionData)
{
    float TimeSinceLastAccessInDays = (FDateTime::UtcNow() - TopicInteractionData.LastAccessedTime).GetTotalDays();

    float Score = (1.0f - TopicInteractionData.ProficiencyScore) + TimeSinceLastAccessInDays;

    return Score;
}


float UContentRecommendationManager::CalculateProficiencyForQuestion(const FString& QuestionText, const FQuestionInteractionData& QuestionInteractionData)
{
    if (QuestionInteractionData.TimesAsked == 0) {
        // If the question has not been tested yet, return a default proficiency value.
        // You might choose to return 0.0 here, or a different value depending on your needs.
        return 0.0f;
    }

    return static_cast<float>(QuestionInteractionData.TimesCorrect) / static_cast<float>(QuestionInteractionData.TimesAsked);
}


float UContentRecommendationManager::CalculateProficiencyForSubTopic(const FSubtopicInteractionData& SubTopicInteractionData)
{
    if (SubTopicInteractionData.Questions.Num() == 0) {
        // If there are no questions in this topic, return a default proficiency value.
        // You might choose to return 0.0 here, or a different value depending on your needs.

        UE_LOG(LogTemp, Warning, TEXT("No questions in this subtopic."));

        return 0.0f;
    }

    float TotalProficiency = 0.0f;
    for (const auto& QuestionPair : SubTopicInteractionData.Questions) {
        float ProficiencyForThisQuestion = CalculateProficiencyForQuestion(QuestionPair.Key, QuestionPair.Value);
        TotalProficiency += ProficiencyForThisQuestion;

        //// Print TimesTested and TimesCorrect for each question
        //UE_LOG(LogTemp, Warning, TEXT("Question: %s, TimesAsked: %d, TimesCorrect: %d, Proficiency: %f"),
        //    *QuestionPair.Key,
        //    QuestionPair.Value.TimesAsked,
        //    QuestionPair.Value.TimesCorrect,
        //    ProficiencyForThisQuestion);
    }

    float ProficiencyForSubtopic = TotalProficiency / static_cast<float>(SubTopicInteractionData.Questions.Num());

    // Print the calculated proficiency for the subtopic
    UE_LOG(LogTemp, Warning, TEXT("Calculated proficiency for subtopic: %f"), ProficiencyForSubtopic);

    return ProficiencyForSubtopic;
}


float UContentRecommendationManager::CalculateProficiencyForTopic(const FTopicInteractionData& TopicInteractionData)
{
    if (TopicInteractionData.Subtopics.Num() == 0) {
        // If there are no subtopics in this topic, return a default proficiency value.

        UE_LOG(LogTemp, Warning, TEXT("No questions in this subtopic."));

        return 0.0f;
    }

    float TotalProficiency = 0.0f;
    for (const auto& SubTopicPair : TopicInteractionData.Subtopics) {
        TotalProficiency += CalculateProficiencyForSubTopic(SubTopicPair.Value);
    }

    return TotalProficiency / static_cast<float>(TopicInteractionData.Subtopics.Num());
}


float UContentRecommendationManager::CalculateProficiencyForSection(const FSectionInteractionData& SectionInteractionData)
{
    if (SectionInteractionData.Topics.Num() == 0) {
        return 0.0f;
    }

    float TotalProficiency = 0.0f;
    for (const auto& TopicPair : SectionInteractionData.Topics) {
        TotalProficiency += CalculateProficiencyForTopic(TopicPair.Value);
    }

    return TotalProficiency / static_cast<float>(SectionInteractionData.Topics.Num());
}


float UContentRecommendationManager::CalculateProficiencyForSubject(const FSubjectInteractionData& SubjectInteractionData)
{
    if (SubjectInteractionData.Sections.Num() == 0) {
        return 0.0f;
    }

    float TotalProficiency = 0.0f;
    for (const auto& SectionPair : SubjectInteractionData.Sections) {
        TotalProficiency += CalculateProficiencyForSection(SectionPair.Value);
    }

    return TotalProficiency / static_cast<float>(SubjectInteractionData.Sections.Num());
}


float UContentRecommendationManager::CalculateProficiencyForSubjectGroup(const FSubjectGroupInteractionData& SubjectGroupInteractionData)
{
    if (SubjectGroupInteractionData.Subjects.Num() == 0) {
        return 0.0f;
    }

    float TotalProficiency = 0.0f;
    for (const auto& SubjectPair : SubjectGroupInteractionData.Subjects) {
        TotalProficiency += CalculateProficiencyForSubject(SubjectPair.Value);
    }

    return TotalProficiency / static_cast<float>(SubjectGroupInteractionData.Subjects.Num());
}


float UContentRecommendationManager::CalculateProficiencyForArea(const FAreaInteractionData& AreaInteractionData)
{
    if (AreaInteractionData.SubjectGroups.Num() == 0) {
        return 0.0f;
    }

    float TotalProficiency = 0.0f;
    for (const auto& SubjectGroupPair : AreaInteractionData.SubjectGroups) {
        TotalProficiency += CalculateProficiencyForSubjectGroup(SubjectGroupPair.Value);
    }

    return TotalProficiency / static_cast<float>(AreaInteractionData.SubjectGroups.Num());
}


float UContentRecommendationManager::CalculateProficiencyForField(const FFieldInteractionData& FieldInteractionData)
{
    if (FieldInteractionData.Areas.Num() == 0) {
        return 0.0f;
    }

    float TotalProficiency = 0.0f;
    for (const auto& AreaPair : FieldInteractionData.Areas) {
        TotalProficiency += CalculateProficiencyForArea(AreaPair.Value);
    }

    return TotalProficiency / static_cast<float>(FieldInteractionData.Areas.Num());
}

