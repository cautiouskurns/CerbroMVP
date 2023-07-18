// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "SubTopicWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API USubTopicWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
    FString Title;

    UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
    FString Content;

    UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
    FString Question;
	
};
