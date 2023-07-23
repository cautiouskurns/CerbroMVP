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

// Only here to stop an error with nowledgeStructs.generated.h compiling when content removed. To be fixed
USTRUCT(BlueprintType)
struct FQuestionInteractionDataTmp
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

