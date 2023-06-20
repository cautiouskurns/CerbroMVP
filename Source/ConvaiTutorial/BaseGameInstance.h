// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReadWriteJsonFile.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FSectionStruct SectionStruct;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FTopic TopicStruct;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FSubtopic SubTopicStruct;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FTest QuestionStruct;
};