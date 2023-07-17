// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "HierarchySubjectWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UHierarchySubjectWidget : public UUserWidget
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
    void AddChildWidget(UResourceWidget* NewChildWidget);

    void AddResourcesWidget(UResourceWidget* ResourcesWidget);

    UFUNCTION(BlueprintCallable, Category = "Custom")
    void OnHierarchySubjectButtonClicked();

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UVerticalBox* ResourcesBox;

    // Other widget code...

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TArray<UResourceWidget*> ChildWidgets;
};

