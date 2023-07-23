// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"

#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"

#include "FieldDataManager.generated.h"


class UUserInteractionDataManager;  // Forward declaration

UENUM(BlueprintType)
enum class EInputType : uint8
{
    JSON,
    CSV,
    DirectInput,
    SAV,
    URL
};

USTRUCT(BlueprintType)
struct FTest
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Question;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FString> Answers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString CorrectAnswer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int TimesTested;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int TimesCorrect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float ProficiencyScore;
};


USTRUCT(BlueprintType)
struct FInteractionMetadata
{
    GENERATED_BODY()

public:
    // The text of the question that was asked
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString QuestionText;

    // The user's answer to the question
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString UserAnswer;

    // Was the user's answer correct?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bIsCorrect;

    // When did the user answer the question?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDateTime ResponseTime;

    // Which AI instructor was being used?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString AIInstructor;

    // Which section was the user in when this interaction occurred?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString SectionName;

    // Which topic was the user studying when this interaction occurred?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString TopicName;

    // Which subtopic was the user studying when this interaction occurred?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString SubtopicName;

    // Was this interaction part of a test or free study?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString StudyMode;

    // How long did the user spend on this question?
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float TimeSpent;
};

USTRUCT(BlueprintType)
struct FSubtopicMetadata
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Author;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDateTime LastUpdated;
};


USTRUCT(BlueprintType)
struct FSubtopic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Content;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FTest> Questions;
};


USTRUCT(BlueprintType)
struct FTopic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FSubtopic> Subtopics;
};


USTRUCT(BlueprintType)
struct FSectionStruct : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString SectionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FTopic> Topics;
};


USTRUCT(BlueprintType)
struct FSubjectStruct : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString SubjectName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FSectionStruct> SubjectDetailsArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FInteractionMetadata> InteractionMetadataArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        EInputType InputType;
};


USTRUCT(BlueprintType)
struct FSubjectGroupStruct : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString SubjectGroupName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FSubjectStruct> Subjects;
};

USTRUCT(BlueprintType)
struct FAreaStruct : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString AreaName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FSubjectGroupStruct> SubjectGroups;
};

USTRUCT(BlueprintType)
struct FFieldStruct : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString FieldName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FAreaStruct> Areas;
};













USTRUCT(BlueprintType)
struct FTopicDataTestStruct
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, Category = "Interaction Data")
    FName TopicName;
};


UCLASS(Blueprintable)
class CONVAITUTORIAL_API UFieldDataManager : public UObject
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Topic")
    void RegisterObserver(UUserInteractionDataManager* observer);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void UnregisterObserver(UUserInteractionDataManager* observer);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AccessSection(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName);

    void AccessSubject(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName);

    void AccessSubjectGroup(FName FieldName, FName AreaName, FName SubjectGroupName);

    void AccessArea(FName FieldName, FName AreaName);

    void AccessField(FName FieldName);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AccessTopic(FName FieldName, FName AreaName, FName SubjectGroupName, FName SubjectName, FName SectionName, FName TopicName);

    int32 GetFieldIndex(FName FieldName);

    int32 GetAreaIndex(int32 FieldIndex, FName AreaName);

    int32 GetSubjectGroupIndex(int32 FieldIndex, int32 AreaIndex, FName SubjectGroupName);

    int32 GetSubjectIndex(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, FName SubjectName);

    int32 GetSectionIndex(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, FName SectionName);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddTopic(FName TopicName);

    FString ToString() const;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
    TArray<FTopicDataTestStruct> Topics;


private:
    TArray<UUserInteractionDataManager*> Observers;
};
