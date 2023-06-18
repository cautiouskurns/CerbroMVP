// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MasterTopicWidget.h"
#include "Components/VerticalBox.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Topic")
    void AddMasterTopicWidgetToHUD(UMasterTopicWidget* MasterTopicWidget);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UVerticalBox* MasterTopicsBox;
	
};
