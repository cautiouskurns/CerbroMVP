// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseGameInstance.h"
#include "ReadWriteJsonFile.h"
#include "AssessmentMetricsCalculator.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UAssessmentMetricsCalculator : public UObject
{
	GENERATED_BODY()

private:
	UBaseGameInstance* GameInstance;

public:
	UAssessmentMetricsCalculator(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{
		// Initialize GameInstance or other properties here if necessary
	}

	void SetGameInstance(UBaseGameInstance* InGameInstance)
	{
		GameInstance = InGameInstance;
	}


	// Calculate total times a question has been asked in a set of questions
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForQuestions(const TArray<FTest>& Questions);

	// Calculate total times questions have been asked in a subtopic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSubtopic(const FSubtopic& Subtopic);

	// Calculate total times questions have been asked in a topic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForTopic(const FTopic& Topic);

	// Calculate total times questions have been asked in a section
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSection(const FSectionStruct& Section);

	// Calculate total times questions have been asked in a subject
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSubject(const FSubjectStruct& Subject);


	// Helper function to calculate total times correct for a set of questions
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForQuestions(const TArray<FTest>& Questions);

	// Calculate total times questions have been answered correctly in a subtopic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSubtopic(const FSubtopic& Subtopic);

	// Calculate total times questions have been answered correctly in a topic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForTopic(const FTopic& Topic);

	// Calculate total times questions have been answered correctly in a section
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSection(const FSectionStruct& Section);

	// Calculate total times questions have been answered correctly in a subject
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSubject(const FSubjectStruct& Subject);



// INCREMENTAL REFACTORING FUNCTIONS
public:
	// Calculate total times questions have been answered for a specific subtopic, given its title
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSubtopicIR(const FString& SubtopicTitle, const TArray<FSubjectStruct>& SubjectDataArray);

	// Calculate total times questions have been answered correctly for a specific subtopic, given its title
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle, const TArray<FSubjectStruct>& SubjectDataArray);
	
};
