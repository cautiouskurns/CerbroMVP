// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TreeViewItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CONVAITUTORIAL_API UTreeViewItem : public UObject
{
	GENERATED_BODY()


public:
    // The name of this item.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TreeView")
    FString Name;

    // The parent of this item. nullptr for root items.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TreeView")
    UTreeViewItem* Parent;

    // The children of this item.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TreeView")
    TArray<UTreeViewItem*> Children;

    UFUNCTION(BlueprintCallable, Category = "TreeView")
    virtual void AddChild(UTreeViewItem* Child);

    UFUNCTION(BlueprintCallable, Category = "TreeView")
    virtual void RemoveChild(UTreeViewItem* Child);

    UFUNCTION(BlueprintCallable, Category = "TreeView")
    void SetName(FString NewName);

    UFUNCTION(BlueprintCallable, Category = "TreeView")
    FString GetName() const { return Name; }

};
