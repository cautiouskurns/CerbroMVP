// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ConvaiTutorial/TestWidget.h"

#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere); // , meta = (BindWidget))
	UTextBlock* SubTopicContentText;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere); // , meta = (BindWidget))
	UTextBlock* SubTopicTitleText;

	UFUNCTION(BlueprintCallable, Category = "Interact Widget")
	void UpdateText(const FString& NewText, const FString& NewTextTitle);

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	UTestWidget* TestWidgetInstance;
	
};
