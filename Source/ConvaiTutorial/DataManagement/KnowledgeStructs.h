// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "KnowledgeStructs.generated.h"

/**
 * 
 */
class CONVAITUTORIAL_API KnowledgeStructs
{
public:
	KnowledgeStructs();
	~KnowledgeStructs();
};

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

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //FSubtopicMetadata Metadata;
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
struct FQuestionInteractionData
{
    GENERATED_BODY()

public:

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
    FDateTime DateLastAccessed;

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
    FDateTime DateLastAccessed;

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
    FDateTime DateLastAccessed;

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
    FDateTime DateLastAccessed;

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
    FDateTime DateLastAccessed;

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
    FDateTime DateLastAccessed;

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
    FDateTime DateLastAccessed;

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


