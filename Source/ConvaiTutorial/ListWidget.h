// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "ListViewItemBase.generated.h"
#include "ListWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void PopulateListView();

private:
    UPROPERTY(meta = (BindWidget))
    UListView* ItemListView;
};
