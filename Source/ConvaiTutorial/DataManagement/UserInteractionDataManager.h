// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserInteractionDataManager.generated.h"

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
 void UpdateAccess(FName TopicName);

 UFUNCTION(BlueprintCallable, Category = "Topic")
int32 GetTimesAccessed(FName TopicName);

 UFUNCTION(BlueprintCallable, Category = "Topic")
 void AddInteraction(FName TopicName);

public:
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
TArray<FUserInteractionStruct> UserInteractions;
	
};
