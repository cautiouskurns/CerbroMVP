// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//#include "ConvaiTutorial/DataManagement/FieldDataManager.h"

#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"

#include "UserInteractionDataManager.generated.h"



class UFieldDataManager;  // Forward declaration

USTRUCT(BlueprintType)
struct FQuestionInteractionData
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString QuestionText;

    UPROPERTY(BlueprintReadWrite)
    int32 TimesAsked;

    UPROPERTY(BlueprintReadWrite)
    int32 TimesCorrect;

    UPROPERTY(BlueprintReadWrite)
    int32 TimesInCorrect;

    UPROPERTY(BlueprintReadWrite)
    float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
    float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
    float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
    FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
    FDateTime SpacedRepetitionNextDate;
};

USTRUCT(BlueprintType)
struct FSubtopicInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
    int32 TimesAccessed;

    UPROPERTY(BlueprintReadWrite)
    float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
    float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
    float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
    FDateTime SpacedRepetitionNextDate;

    UPROPERTY(BlueprintReadWrite)
    FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
    TMap<FString, FQuestionInteractionData> Questions;
};

USTRUCT(BlueprintType)
struct FTopicInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
        int32 TimesAccessed;

    UPROPERTY(BlueprintReadWrite)
        float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
        float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        FDateTime SpacedRepetitionNextDate;

    UPROPERTY(BlueprintReadWrite)
        FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
        TMap<FString, FSubtopicInteractionData> Subtopics;
};

USTRUCT(BlueprintType)
struct FSectionInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
        int32 TimesAccessed;

    UPROPERTY(BlueprintReadWrite)
        float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
        float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        FDateTime SpacedRepetitionNextDate;

    UPROPERTY(BlueprintReadWrite)
        FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
        TMap<FString, FTopicInteractionData> Topics;
};

USTRUCT(BlueprintType)
struct FSubjectInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
        int32 TimesAccessed;

    UPROPERTY(BlueprintReadWrite)
        float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
        float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        FDateTime SpacedRepetitionNextDate;

    UPROPERTY(BlueprintReadWrite)
        FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
        TMap<FString, FSectionInteractionData> Sections;
};

USTRUCT(BlueprintType)
struct FSubjectGroupInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
        int32 TimesAccessed;

    UPROPERTY(BlueprintReadWrite)
        float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
        float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        FDateTime SpacedRepetitionNextDate;

    UPROPERTY(BlueprintReadWrite)
        FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
        TMap<FString, FSubjectInteractionData> Subjects;
};

USTRUCT(BlueprintType)
struct FAreaInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
        int32 TimesAccessed;

    UPROPERTY(BlueprintReadWrite)
        float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
        float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        FDateTime SpacedRepetitionNextDate;

    UPROPERTY(BlueprintReadWrite)
        FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
        TMap<FString, FSubjectGroupInteractionData> SubjectGroups;
};

USTRUCT(BlueprintType)
struct FFieldInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
        int32 TimesAccessed;

    UPROPERTY(BlueprintReadWrite)
        float ProficiencyScore;

    UPROPERTY(BlueprintReadWrite)
        float LastInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        float AverageInteractionDuration;

    UPROPERTY(BlueprintReadWrite)
        FDateTime SpacedRepetitionNextDate;

    UPROPERTY(BlueprintReadWrite)
        FDateTime LastAccessedTime;

    UPROPERTY(BlueprintReadWrite)
        TMap<FString, FAreaInteractionData> Areas;
};

USTRUCT(BlueprintType)
struct FUserInteractionData
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
       TMap<FString, FFieldInteractionData> Fields;
};




USTRUCT(BlueprintType)
struct FUserInteractionStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Interaction Data")
    FName TopicName;

    UPROPERTY(BlueprintReadWrite, Category = "Interaction Data")
    int32 TimesAccessed;
};


UCLASS(Blueprintable)
class CONVAITUTORIAL_API UUserInteractionDataManager : public UObject
{
	GENERATED_BODY()

public:

 UFUNCTION(BlueprintCallable, Category = "Topic")
 void UpdateAccess(FName FieldName, FName AreaName = "", FName SubjectGroupName = "", FName SubjectName = "", FName SectionName = "", FName TopicName = "");


 UFUNCTION(BlueprintCallable, Category = "Topic")
 int32 GetTimesAccessed(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName);

 //UFUNCTION(BlueprintCallable, Category = "Topic")
 //void UpdateQuestionMetrics(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, bool Correct);






//public:
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
//TArray<FUserInteractionStruct> UserInteractions;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
    FUserInteractionData UserInteractions;

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddInteraction(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeUserInteractions(const TArray<FFieldStruct>& FieldDataArray);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeField(const FFieldStruct& Field, FFieldInteractionData& FieldInteractionData);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeArea(const FAreaStruct& Area, FAreaInteractionData& AreaInteractionData);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeSubjectGroup(const FSubjectGroupStruct& SubjectGroup, FSubjectGroupInteractionData& SubjectGroupInteractionData);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeSubject(const FSubjectStruct& Subject, FSubjectInteractionData& SubjectInteractionData);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeSection(const FSectionStruct& Section, FSectionInteractionData& SectionInteractionData);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeTopic(const FTopic& Topic, FTopicInteractionData& TopicInteractionData);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeSubtopic(const FSubtopic& Subtopic, FSubtopicInteractionData& SubtopicInteractionData);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void InitializeQuestion(const FTest& Question, FQuestionInteractionData& QuestionInteractionData);

    FString ToString() const;

    FQuestionInteractionData GetQuestionInteractionData(const FString& QuestionText);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void UpdateQuestionInteractionData(FString FieldName, FString AreaName, FString SubjectGroupName, FString SubjectName, FString SectionName, FString TopicName, FString SubtopicName, FString QuestionText, bool IsAnswerCorrect);


    void SetUserInteractions(const FUserInteractionData& NewUserInteractions);

    const FUserInteractionData& GetUserInteractions() const;

    const FFieldInteractionData* GetFieldInteractionData(const FString& FieldName) const;

    const FAreaInteractionData* GetAreaInteractionData(const FString& AreaName, const FFieldInteractionData& FieldData) const;

    const FSubjectGroupInteractionData* GetSubjectGroupInteractionData(const FString& SubjectGroupName, const FAreaInteractionData& AreaData) const;

    const FSubjectInteractionData* GetSubjectInteractionData(const FString& SubjectName, const FSubjectGroupInteractionData& SubjectGroupData) const;

    const FSectionInteractionData* GetSectionInteractionData(const FString& SectionName, const FSubjectInteractionData& SubjectData) const;

    const FTopicInteractionData* GetTopicInteractionData(const FString& TopicName, const FSectionInteractionData& SectionData) const;

    const FSubtopicInteractionData* GetSubtopicInteractionData(const FString& SubtopicName, const FTopicInteractionData& TopicData) const;

    const FQuestionInteractionData* GetQuestionInteractionData(const FString& QuestionText, const FSubtopicInteractionData& SubtopicData) const;

    int32 CalculateTimesAskedForSubtopic(const FString& SubtopicName, const FTopicInteractionData& TopicData);


};
