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


	UFUNCTION(BlueprintCallable, Category = "Interact Widget")
	void PopulateFieldComboBox(UComboBoxString* ComboBox);

	UFUNCTION(BlueprintCallable, Category = "Interact Widget")
	void PopulateAreaComboBox(UComboBoxString* ComboBox, const FString& SelectedField);

	UFUNCTION(BlueprintCallable, Category = "Interact Widget")
	void PopulateSubjectGroupComboBox(UComboBoxString* ComboBox, const FString& SelectedArea);

	UFUNCTION(BlueprintCallable, Category = "Interact Widget")
	void PopulateSubjectComboBox(UComboBoxString* ComboBox, const FString& SelectedSubjectGroup);

	UFUNCTION(BlueprintCallable, Category = "Interact Widget")
	void PopulateSectionComboBox(UComboBoxString* ComboBox, const FString& SelectedSubject);


	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	UTestWidget* TestWidgetInstance;
	
};
