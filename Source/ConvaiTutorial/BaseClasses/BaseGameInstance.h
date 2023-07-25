// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"
#include "ConvaiTutorial/DataManagement/KnowledgeStructs.h"
#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"
#include "ConvaiTutorial/DataManagement/FieldDataManager.h"

#include "ConvaiTutorial/Widgets/DirectoryHierarchyManager.h"
#include "ConvaiTutorial/Widgets/FieldWidget.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include <Components/TreeView.h>
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

#include "BaseGameInstance.generated.h"


UENUM(BlueprintType)
enum class EStructLevelJSON : uint8
{
	EL_Field,
	EL_Area,
	EL_SubjectGroup,
	EL_Subject,
	EL_Section,
	EL_Topic,
	EL_Subtopic
};


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
	int FieldIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int AreaIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	int SubjectGroupIndex;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	FRandomStream RandStream;

	FQuestionSelector()
	{
		RandStream.GenerateNewSeed();  // Generate a new random seed
	}

};


class UDataProvider;
class UAssessmentMetricsCalculator;
class UContentRecommendationManager;

UCLASS()
class CONVAITUTORIAL_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBaseGameInstance();

	virtual void Init() override;

	// Declare a pointer to UAssessmentMetricsCalculator
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	UAssessmentMetricsCalculator* AssessmentMetricsCalculator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	UContentRecommendationManager* ContentRecommendationManager;

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


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test Structs")
	TArray<FTopicDataTestStruct> TopicTestDataArray;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test Structs")
	UFieldDataManager* FieldDataManager;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test Structs")
	UUserInteractionDataManager* UserInteractionDataManager;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test Structs")
	//UAssessmentMetricsCalculator* AssessmentMetricsCalculator;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void InitializeDataManagers();

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
	int32 CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle);


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FTest UpdateTimesTestedAndCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, const FString& SelectedAnswer);


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FString SubmitAnswer(const FString& AnswerText);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FTest UpdateAnswerStatus(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText);


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 GetTimesTestedForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText);


	UAssessmentMetricsCalculator* AssessmentMetricsCalculatorGlobal;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 GetTimesCorrectForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText);


	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FSubjectStruct LoadJsonFromFile(FString FilePath);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void LoadJsonArrayFromFile(FString FilePath, EStructLevelJSON StructLevel, const FString& ParentName);



	FFieldStruct* FindFieldByName(const FString& FieldName);

	FAreaStruct* FindAreaByName(const FString& AreaName);

	FSubjectGroupStruct* FindSubjectGroupByName(const FString& SubjectGroupName);

	FSubjectStruct* FindSubjectByName(const FString& SubjectName);

	FSectionStruct* FindSectionByName(const FString& SectionName);

	FTopic* FindTopicByName(const FString& TopicName);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void LoadDataFromCSV(const FString& FilePath);


	const FFieldInteractionData* GetFieldInteractionData(const FString& FieldName);

	const FAreaInteractionData* GetAreaInteractionData(const FString& AreaName, const FFieldInteractionData& FieldData);

	const FSubjectGroupInteractionData* GetSubjectGroupInteractionData(const FString& SubjectGroupName, const FAreaInteractionData& AreaData);

	const FSubjectInteractionData* GetSubjectInteractionData(const FString& SubjectName, const FSubjectGroupInteractionData& SubjectGroupData);

	const FSectionInteractionData* GetSectionInteractionData(const FString& SectionName, const FSubjectInteractionData& SubjectData);

	const FTopicInteractionData* GetTopicInteractionData(const FString& TopicName, const FSectionInteractionData& SectionData);

	const FSubtopicInteractionData* GetSubtopicInteractionData(const FString& SubtopicName, const FTopicInteractionData& TopicData);

	
	
	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateProficiencyForSubtopic(const FString& SubtopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateProficiencyForTopic(const FString& TopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateProficiencyForSection(const FString& SectionName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateProficiencyForSubject(const FString& SubjectName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateProficiencyForSubjectGroup(const FString& SubjectGroupName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateProficiencyForArea(const FString& AreaName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateProficiencyForField(const FString& FieldName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateSubtopicRecommendationScore(const FString& SubtopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateTopicRecommendationScore(const FString& TopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	float CalculateSectionRecommendationScore(const FString& SectionName);





	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 CalculateTimesAskedForSubtopic(const FString& SubtopicName, const FTopicInteractionData& TopicData);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesAskedForSubtopicInteract(const FString& SubtopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesAskedForTopicInteract(const FString& TopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesAskedForSectionInteract(const FString& SectionName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesAskedForSubjectInteract(const FString& SubjectName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesAskedForSubjectGroupInteract(const FString& SubjectGroupName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesAskedForAreaInteract(const FString& AreaName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesAskedForFieldInteract(const FString& FieldName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesCorrectForSubtopicInteract(const FString& SubtopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesCorrectForTopicInteract(const FString& TopicName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesCorrectForSectionInteract(const FString& SectionName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesCorrectForSubjectInteract(const FString& SubjectName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesCorrectForSubjectGroupInteract(const FString& SubjectGroupName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesCorrectForAreaInteract(const FString& AreaName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	int32 CalculateTimesCorrectForFieldInteract(const FString& FieldName);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	void UpdateProficiencyForSubtopic(const FString& SubtopicName, float NewProficiencyScore);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	void UpdateProficiencyForTopic(const FString& TopicName, float NewProficiencyScore);

	UFUNCTION(BlueprintCallable, Category = "Question Metrics")
	void UpdateProficiencyForSection(const FString& SectionName, float NewProficiencyScore);



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	UDataProvider* DataProvider;

	UPROPERTY(BlueprintReadOnly, Category = "Directory")
	UDirectoryHierarchyManager* DirectoryManager;
};
