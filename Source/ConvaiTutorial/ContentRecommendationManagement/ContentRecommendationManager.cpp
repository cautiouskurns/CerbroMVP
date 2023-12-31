// Fill out your copyright notice in the Description page of Project Settings.


#include "ContentRecommendationManager.h"
#include <ConvaiTutorial/MetricHandling/AssessmentMetricsCalculator.h>
#include <ConvaiTutorial/DataManagement/UserInteractionDataManager.h>


void UContentRecommendationManager::InitializeDataManagers(UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    // Store a reference to UserInteractionDataManager
    UserInteractionDataManager = UserInteractionDataManagerLocal;
}

float UContentRecommendationManager::CalculateSubtopicRecommendationScore(const FSubtopicInteractionData& SubtopicInteractionData)
{
    //float TimeSinceLastAccessInDays = (FDateTime::UtcNow() - SubtopicInteractionData.LastAccessedTime).GetTotalDays();

    float TimeSinceLastAccessInDays = (FDateTime::UtcNow() - FDateTime(2023, 7, 24, 12, 30, 0)).GetTotalDays();
    float normalizedTime = TimeSinceLastAccessInDays / 30.0f;

    float Score = (1.0f - SubtopicInteractionData.ProficiencyScore) + normalizedTime;
    float normalizedScore = FMath::GetMappedRangeValueClamped(FVector2D(0, 2), FVector2D(0, 1), Score);

    return normalizedScore;
}

float UContentRecommendationManager::CalculateTopicRecommendationScore(const FTopicInteractionData& TopicInteractionData)
{

    //float TimeSinceLastAccessInDays = (FDateTime::UtcNow() - TopicInteractionData.LastAccessedTime).GetTotalDays();

    float TimeSinceLastAccessInDays = (FDateTime::UtcNow() - FDateTime(2023, 7, 24, 12, 30, 0)).GetTotalDays();
    float normalizedTime = TimeSinceLastAccessInDays / 30.0f;

    float Score = (1.0f - TopicInteractionData.ProficiencyScore) + normalizedTime;
    float normalizedScore = FMath::GetMappedRangeValueClamped(FVector2D(0, 2), FVector2D(0, 1), Score);

    return normalizedScore;
}

float UContentRecommendationManager::CalculateSectionRecommendationScore(const FSectionInteractionData& SectionInteractionData)
{
    //float TimeSinceLastAccessInDays = (FDateTime::UtcNow() - SectionInteractionData.LastAccessedTime).GetTotalDays();

    float TimeSinceLastAccessInDays = (FDateTime::UtcNow() - FDateTime(2023, 7, 24, 12, 30, 0)).GetTotalDays();
    float normalizedTime = TimeSinceLastAccessInDays / 30.0f;

    float Score = (1.0f - SectionInteractionData.ProficiencyScore) + normalizedTime;
    float normalizedScore = FMath::GetMappedRangeValueClamped(FVector2D(0, 2), FVector2D(0, 1), Score);

    return normalizedScore;
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


float UContentRecommendationManager::CalculateProficiencyForSubtopic(const FSubtopicInteractionData& SubTopicInteractionData)
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
        TotalProficiency += CalculateProficiencyForSubtopic(SubTopicPair.Value);
    }

    float NewProficiencyScore = TotalProficiency / static_cast<float>(TopicInteractionData.Subtopics.Num());

    return NewProficiencyScore;
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


//const FSubtopicInteractionData* UContentRecommendationManager::FindSubtopicInteractionDataByName(const FString& SubtopicName)
//{
//    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();
//
//    for (const auto& FieldPair : UserInteractions.Fields)
//    {
//        for (const auto& AreaPair : FieldPair.Value.Areas)
//        {
//            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
//            {
//                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
//                {
//                    for (const auto& SectionPair : SubjectPair.Value.Sections)
//                    {
//                        for (const auto& TopicPair : SectionPair.Value.Topics)
//                        {
//                            for (auto& SubtopicPair : TopicPair.Value.Subtopics)
//                            {
//                                if (SubtopicPair.Key == SubtopicName)
//                                {
//                                    return &SubtopicPair.Value;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return nullptr; // Return nullptr if no subtopic with the given name is found
//}
//
//
//const FTopicInteractionData* UContentRecommendationManager::FindTopicInteractionDataByName(const FString& TopicName)
//{
//    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();
//
//    for (const auto& FieldPair : UserInteractions.Fields)
//    {
//        for (const auto& AreaPair : FieldPair.Value.Areas)
//        {
//            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
//            {
//                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
//                {
//                    for (const auto& SectionPair : SubjectPair.Value.Sections)
//                    {
//                        for (auto& TopicPair : SectionPair.Value.Topics)
//                        {
//                            if (TopicPair.Key == TopicName)
//                            {
//                                return &TopicPair.Value;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return nullptr; // Return nullptr if no topic with the given name is found
//}
//
//
//float UContentRecommendationManager::CalculateProficiencyForTopic(const FString& TopicName)
//{
//    const FTopicInteractionData* TopicData = FindTopicInteractionDataByName(TopicName);
//    if (!TopicData)
//    {
//        return 0.0f; // Return 0.0f if no topic with the given name is found
//    }
//
//    if (TopicData->Subtopics.Num() == 0) {
//        // If there are no subtopics in this topic, return a default proficiency value.
//        UE_LOG(LogTemp, Warning, TEXT("No questions in this subtopic."));
//        return 0.0f;
//    }
//
//    float TotalProficiency = 0.0f;
//    for (const auto& SubTopicPair : TopicData->Subtopics) {
//        TotalProficiency += CalculateProficiencyForSubtopic(SubTopicPair.Value);
//    }
//
//    return TotalProficiency / static_cast<float>(TopicData->Subtopics.Num());
//}