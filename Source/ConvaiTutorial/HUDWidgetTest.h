// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SectionWidget.h"
#include "HUDWidgetTest.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UHUDWidgetTest : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddSectionWidgetToHUD(USectionWidget* SectionWidget);

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UVerticalBox* SectionBox;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SubjectName;
	
};
