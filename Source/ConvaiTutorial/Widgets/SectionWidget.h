// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "ConvaiTutorial/Widgets/TopicWidget.h"

#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "MasterTopicWidget.h"
#include <Components/Image.h>

#include "SectionWidget.generated.h"


/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API USectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddTopicWidget(UTopicWidget* TopicWidget);

    UFUNCTION(BlueprintCallable)
    void OnSectionButtonClicked();

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        UVerticalBox* TopicsBox;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SectionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FTopic> Topics;

};
