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
#include "FieldWidget.h"
#include "DirectoryHierarchyManager.h"
#include "BaseGameInstance.generated.h"



class FJsonObject;



USTRUCT()
struct FTestSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString Question;

	UPROPERTY()
		TArray<FString> Answers;

	UPROPERTY()
		FString CorrectAnswer;

	UPROPERTY()
		int TimesTested;

	UPROPERTY()
		int TimesCorrect;

	UPROPERTY()
		float ProficiencyScore;
};


USTRUCT()
struct FInteractionMetadataSaveData
{
	GENERATED_BODY()

public:
	// The text of the question that was asked
	UPROPERTY()
	FString QuestionText;

	// The user's answer to the question
	UPROPERTY()
	FString UserAnswer;

	// Was the user's answer correct?
	UPROPERTY()
	bool bIsCorrect;

	// When did the user answer the question?
	UPROPERTY()
	FDateTime ResponseTime;

	// Which AI instructor was being used?
	UPROPERTY()
	FString AIInstructor;

	// Which section was the user in when this interaction occurred?
	UPROPERTY()
	FString SectionName;

	// Which topic was the user studying when this interaction occurred?
	UPROPERTY()
	FString TopicName;

	// Which subtopic was the user studying when this interaction occurred?
	UPROPERTY()
	FString SubtopicName;

	// Was this interaction part of a test or free study?
	UPROPERTY()
	FString StudyMode;

	// How long did the user spend on this question?
	UPROPERTY()
	float TimeSpent;
};


USTRUCT()
struct FSubtopicSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString Title;

	UPROPERTY()
	FString Content;

	UPROPERTY()
	TArray<FTestSaveData> QuestionsSaveData;

};


USTRUCT(BlueprintType)
struct FTopicSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString Title;

	UPROPERTY()
	TArray<FSubtopicSaveData> SubtopicsSaveData;
};


USTRUCT(BlueprintType)
struct FSectionStructSaveData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SectionName;

	UPROPERTY()
	TArray<FTopicSaveData> TopicsSaveData;
};


USTRUCT()
struct FSubjectStructSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SubjectName;

	UPROPERTY()
	TArray<FInteractionMetadata> InteractionMetadataArray;

	UPROPERTY()
	TArray<FSectionStructSaveData> SubjectDetailsArraySaveData;

	UPROPERTY()
	EInputType InputType;
};


USTRUCT()
struct FSubjectGroupStructSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SubjectGroupName;

	UPROPERTY()
	TArray<FSubjectStructSaveData> SubjectsSaveData;
};


USTRUCT()
struct FAreaStructSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString AreaName;

	UPROPERTY()
	TArray<FSubjectGroupStructSaveData> SubjectGroupsSaveData;
};

USTRUCT()
struct FFieldStructSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString FieldName;

	UPROPERTY()
	TArray<FAreaStructSaveData> AreasSaveData;
};









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

	//void Init();

	virtual void Init() override;

	TArray<FFieldStruct> Fields;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FFieldStruct> FieldDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FAreaStruct> AreaDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSubjectGroupStruct> SubjectGroupDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSubjectStruct> SubjectDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSectionStruct> SectionDataArray;




	UFUNCTION(BlueprintCallable, Category = "Data")
	void InitializeSubjectDataArray();

	UFUNCTION(BlueprintCallable, Category = "YourCategory")
	void PopulateFieldDataArrayFromDataTable(UDataTable* DataTable);

	UFUNCTION(BlueprintCallable, Category = "YourCategory")
	void SaveGameData();

	UFUNCTION(BlueprintCallable, Category = "YourCategory")
	void LoadGameData();



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

	UPROPERTY(BlueprintReadOnly, Category = "Directory")
	UDirectoryHierarchyManager* DirectoryManager;
};
