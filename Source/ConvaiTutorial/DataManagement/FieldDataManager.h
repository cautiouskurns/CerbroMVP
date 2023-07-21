// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"

#include "UObject/NoExportTypes.h"

#include "FieldDataManager.generated.h"

















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
    void AccessTopic(FName TopicName);

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddTopic(FName TopicName);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
    TArray<FTopicDataTestStruct> Topics;

private:
    TArray<UUserInteractionDataManager*> Observers;
};
