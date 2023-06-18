// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopicWidget.h"
#include "SectionWidget.h"
#include "SubTopicWidget.h"
#include "HUDWidgetTest.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	TArray<FTopic> TopicArray;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	TArray<FSubtopic> SubtopicDataArray;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	USectionWidget* SectionWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UTopicWidget* TopicWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UHUDWidgetTest* HUDTestWidgetReference;
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
		USectionWidget* CreateSectionWidget(const TArray<FTopic>& BlueprintTopicArray, const FSectionStruct& SectionData,
			TSubclassOf<UUserWidget> SectionWidgetClass, TSubclassOf<UUserWidget> TopicWidgetClass, 
			TSubclassOf<UUserWidget> SubtopicWidgetClass, UHUDWidgetTest* InHUDTestWidget);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	TArray<FSubtopic> CreateTopicWidgets(const TArray<FTopic>& BlueprintTopicArray, USectionWidget* InSectionWidget, 
		TSubclassOf<UUserWidget> TopicWidgetClass, TSubclassOf<UUserWidget> SubtopicWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateSubTopicWidgets(const TArray<FSubtopic>& SubTopics, UTopicWidget* TopicWidget,
		TSubclassOf<UUserWidget> SubtopicWidgetClass);
};
