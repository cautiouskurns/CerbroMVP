// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <ConvaiTutorial/DataManagement/UserInteractionDataManager.h>

#include "UObject/NoExportTypes.h"

#include "ContentRecommendationManager.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UContentRecommendationManager : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Recommendation Score")
	float CalculateSubtopicRecommendationScore(const FSubtopicInteractionData& SubtopicInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Recommendation Score")
	float CalculateTopicRecommendationScore(const FTopicInteractionData& TopicInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Recommendation Score")
	float CalculateSectionRecommendationScore(const FSectionInteractionData& SectionInteractionData);


	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForQuestion(const FString& QuestionText, const FQuestionInteractionData& QuestionInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForSubtopic(const FSubtopicInteractionData& TopicInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForTopic(const FTopicInteractionData& TopicInteractionData);


	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForSection(const FSectionInteractionData& SectionInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForSubject(const FSubjectInteractionData& SubjectInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForSubjectGroup(const FSubjectGroupInteractionData& SubjectGroupInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForArea(const FAreaInteractionData& AreaInteractionData);

	UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	float CalculateProficiencyForField(const FFieldInteractionData& FieldInteractionData);

	//UFUNCTION(BlueprintCallable, Category = "Proficiency Score")
	//void SetUserInteractionDataManager(UUserInteractionDataManager* manager);
};
