// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"
#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "UObject/NoExportTypes.h"

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



	UAssessmentMetricsCalculator(UObject* ObjectInitializer, UUserInteractionDataManager* manager);

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

	// INCREMENTAL REFACTORING FUNCTIONS
public:
	// Calculate total times questions have been answered for a specific subtopic, given its title
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSubtopicIR(const FString& SubtopicTitle, const TArray<FFieldStruct>& FieldDataArray);


	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSubtopicInteract(const FString& SubtopicName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForTopicInteract(const FString& TopicName, UUserInteractionDataManager* UserInteractionDataManager);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSectionInteract(const FString& SectionName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSubjectInteract(const FString& SubjectName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForSubjectGroupInteract(const FString& SubjectGroupName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForAreaInteract(const FString& AreaName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForFieldInteract(const FString& FieldName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSubtopicInteract(const FString& SubtopicName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForTopicInteract(const FString& TopicName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSectionInteract(const FString& SectionName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSubjectInteract(const FString& SubjectName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSubjectGroupInteract(const FString& SubjectGroupName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForAreaInteract(const FString& AreaName, UUserInteractionDataManager* UserInteractionDataManagerLocal);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForFieldInteract(const FString& FieldName, UUserInteractionDataManager* UserInteractionDataManagerLocal);



	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesAskedForQuestionsIndividual(const TArray<FTest>& Questions);

	//UFUNCTION(BlueprintCallable, Category = "Assessment")
	//int32 CalculateTimesAskedForQuestionIR(const FString& QuestionText, const TArray<FFieldStruct>& FieldDataArray);



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
	// Calculate total times questions have been answered correctly for a specific subtopic, given its title
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle, const TArray<FFieldStruct>& FieldDataArray);



	// Calculate total times questions have been answered incorrectly for a set of questions
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesCorrectForQuestion(FTest& Question, const FString& SelectedAnswer);
	
	// Calculate total times questions have been answered incorrectly in a subtopic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesCorrectForSubtopic(FSubtopic& Subtopic, int32 QuestionIndex, const FString& SelectedAnswer);

	// Calculate total times questions have been answered incorrectly in a topic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesCorrectForTopic(FTopic& Topic, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer);

	// Calculate total times questions have been answered incorrectly in a section
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesCorrectForSection(FSectionStruct& Section, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer);

	// Calculate total times questions have been answered incorrectly in a subject
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesCorrectForSubject(FSubjectStruct& Subject, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer);

	// Calculate total times questions have been answered correctly overall
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesCorrect(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer, TArray<FSubjectStruct>& SubjectDataArray);



	// Calculate total times questions have been answered overall
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesTestedForQuestion(FTest& Question);

	// Calculate total times questions have been asked in a subtopic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesTestedForSubtopic(FSubtopic& Subtopic, int32 QuestionIndex);

	// Calculate total times questions have been asked in a topic
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesTestedForTopic(FTopic& Topic, int32 SubtopicIndex, int32 QuestionIndex);

	// Calculate total times questions have been asked in a section
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesTestedForSection(FSectionStruct& Section, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex);

	// Calculate total times questions have been asked in a subject
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateTimesTestedForSubject(FSubjectStruct& Subject, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex);

	// Calculate total times questions have been asked overall
	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 UpdateRandomQuestionTimesTested(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, TArray<FSubjectStruct>& SubjectDataArray);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	FTest UpdateTimesTestedAndCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, const FString& SelectedAnswer, TArray<FSubjectStruct>& SubjectDataArray);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	FTest UpdateAnswerStatus(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray);


	UFUNCTION(BlueprintCallable, Category = "Assessment")
	FString SubmitAnswer(const FString& AnswerText);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 GetTimesTestedForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray);

	UFUNCTION(BlueprintCallable, Category = "Assessment")
	int32 GetTimesCorrectForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray);

	void SetUserInteractionDataManager(UUserInteractionDataManager* manager);

	UUserInteractionDataManager* UserInteractionDataManager;

	private:
		FString SubmittedAnswer;

};



