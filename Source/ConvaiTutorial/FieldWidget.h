// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopicWidget.h"
#include "Components/VerticalBox.h"
#include "FieldWidget.generated.h"


/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UFieldWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void SetName(const FString& NewName);

    // Other widget code...

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FString Name;


public:
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void AddChildWidget(UAreaWidget* NewChildWidget);

    void AddAreaWidget(UAreaWidget* AreaWidget);

    UFUNCTION(BlueprintCallable, Category = "Custom")
    void OnFieldButtonClicked();

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UVerticalBox* AreaBox;

    // Other widget code...

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TArray<UAreaWidget*> ChildWidgets;
};
