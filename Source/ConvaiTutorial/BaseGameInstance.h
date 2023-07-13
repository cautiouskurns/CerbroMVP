// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "ReadWriteJsonFile.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include <Components/TreeView.h>
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "KnowledgeStructs.h"
#include "BaseGameInstance.generated.h"


class FJsonObject;

USTRUCT(BlueprintType)
struct FImageTestStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ImageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TestTexture;
};






USTRUCT(BlueprintType)
struct FSubjectStructBasic : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SubjectName;
};

USTRUCT(BlueprintType)
struct FTopicStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TopicName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Subtopics;
};

USTRUCT(BlueprintType)
struct FSubjectStructComplex : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SubjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTopicStruct> Topics;
};






USTRUCT(BlueprintType)
struct FQuestionSelector
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int SubjectIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int SectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int TopicIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int SubTopicIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int QuestionIndex;

	// Randomization level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int32 RandomizationLevel;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	//// Reference to the data array
	//TArray<FSubjectStruct>* DataArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	// Random number generator
	FRandomStream RandStream;

	FQuestionSelector()
	{
		RandStream.GenerateNewSeed();  // Generate a new random seed
	}

};


class UDataProvider;
class UAssessmentMetricsCalculator;

UCLASS()
class CONVAITUTORIAL_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBaseGameInstance();

	void Init();



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSubjectStruct> SubjectDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSectionStruct> SectionDataArray;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	//FSectionStruct SubjectStruct;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void InitializeSubjectDataArray();



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	FSubjectStruct SubjectData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FTopic> TopicDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSubtopic> SubTopicDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FTest> QuestionDataArray;



	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FSectionStruct SectionStruct;

	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FTopic TopicStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "My Category")
	TArray<FSubtopic> SubTopicStructArray;

	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FTest QuestionStruct;


	UPROPERTY()
	FQuestionSelector CurrentQuestionSelector;

	//UPROPERTY()
	//UAssessmentMetricsCalculator* AssessmentMetricsCalculator;


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor PrimaryColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor SecondaryColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor TertiaryColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor AccentColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor BackgroundColor;


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 UpdateRandomQuestionTimesTested(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 UpdateTimesCorrect(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 CalculateTimesAskedForSubtopicIR(const FString& SubtopicTitle);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 CalculateTimesAskedForQuestionIR(const FString& SubtopicTitle);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle);


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FTest UpdateTimesTestedAndCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, const FString& SelectedAnswer);


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FString SubmitAnswer(const FString& AnswerText);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FTest UpdateAnswerStatus(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 GetTimesTestedForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 GetTimesCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText);

	UAssessmentMetricsCalculator* AssessmentMetricsCalculatorGlobal;

	

	/*UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 UpdateTimesCorrect(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer);*/


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FSubjectStruct LoadJsonFromFile(FString FilePath);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	UDataProvider* DataProvider;
};
