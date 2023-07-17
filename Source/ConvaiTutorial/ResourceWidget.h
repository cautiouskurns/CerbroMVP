// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KnowledgeStructs.h"
#include <Components/Button.h>
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

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FSubjectStruct AssociatedSubject;

    void NativeConstruct();

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void ButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    int32 FindMatchingSubjectIndex();

    UButton* MyButton;
};
