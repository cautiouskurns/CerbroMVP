// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TreeViewItem.h"
#include "SubjectTreeViewItem.generated.h"

UCLASS(Blueprintable)
class CONVAITUTORIAL_API USubjectTreeViewItem : public UTreeViewItem
{
	GENERATED_BODY()

public:
	USubjectTreeViewItem();

virtual void AddChild(UTreeViewItem* Child) override; // Override declared here
	
};
