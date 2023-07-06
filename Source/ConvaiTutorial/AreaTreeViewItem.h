// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TreeViewItem.h"
#include "AreaTreeViewItem.generated.h"

UCLASS(Blueprintable)
class CONVAITUTORIAL_API UAreaTreeViewItem : public UTreeViewItem
{
	GENERATED_BODY()

public:
	UAreaTreeViewItem();
	
virtual void AddChild(UTreeViewItem* Child) override; // Override declared here

};
