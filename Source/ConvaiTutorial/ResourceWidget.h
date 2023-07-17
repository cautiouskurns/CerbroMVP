// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UResourceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void SetName(const FString& NewName);

    // Other widget code...

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FString Name;

//public:
//    UFUNCTION(BlueprintCallable, Category = "Custom")
//    void AddChildWidget(UAreaWidget* NewChildWidget);
//
//    // Other widget code...
//
//private:
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
//    TArray<UAreaWidget*> ChildWidgets;
};
