// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "HierarchySubjectWidget.h"
#include "AreaWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UAreaWidget : public UUserWidget
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
    void AddChildWidget(UHierarchySubjectWidget* NewChildWidget);

    void AddHierarchySubjectWidget(UHierarchySubjectWidget* HierarchySubjectWidget);

    UFUNCTION(BlueprintCallable, Category = "Custom")
    void OnAreaButtonClicked();

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UVerticalBox* HierarchySubjectBox;

    // Other widget code...

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TArray<UHierarchySubjectWidget*> ChildWidgets;
};
