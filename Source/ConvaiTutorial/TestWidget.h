// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TestWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UTestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Declare a pointer to UTextBlock
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TestTextBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TestTitleBox;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void UpdateText(const FText& NewText, const FText& NewTitleText);

};
