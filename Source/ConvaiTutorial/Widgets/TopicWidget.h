// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"
#include "ConvaiTutorial/DataManagement/FieldDataManager.h"

#include "ConvaiTutorial/Widgets/SubTopicWidget.h"

#include "Blueprint/UserWidget.h"

#include "TopicWidget.generated.h"

class UVerticalBox;

UCLASS()
class CONVAITUTORIAL_API UTopicWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // The function to toggle the visibility of the SubtopicsBox
    UFUNCTION(BlueprintCallable)
    void OnTopicButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddSubTopicWidget(USubTopicWidget* SubTopicWidget);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UVerticalBox* SubtopicsBox;

public:
    UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
    FString TopicName;

    UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
    TArray<FSubtopic> Subtopics; // Replace FYourSubtopicStruct with your actual subtopic struct type

};
