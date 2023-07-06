// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameInstance.h"
#include "TreeViewItem.h"
#include "DataProvider.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UDataProvider : public UBaseGameInstance
{
	GENERATED_BODY()

public:
    // Returns the root items
    UFUNCTION(BlueprintCallable, Category = "Data")
    TArray<UTreeViewItem*> GetRootItems();

    // Returns the children of a given item
    UFUNCTION(BlueprintCallable, Category = "Data")
    TArray<UTreeViewItem*> GetChildrenOfItem(UTreeViewItem* Item);

public:
    // This function will construct the hierarchy. Call it in the constructor or in Init function.
    UFUNCTION(BlueprintCallable, Category = "Data")
    void ConstructHierarchy();

    // List of root items
    TArray<UTreeViewItem*> RootItems;
	
};
