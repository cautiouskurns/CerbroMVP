// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopicWidget.h"
#include "MasterTopicWidget.generated.h"


UCLASS()
class CONVAITUTORIAL_API UMasterTopicWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddTopicWidget(UTopicWidget* TopicWidget);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UVerticalBox* TopicsBox;
};
