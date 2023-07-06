// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaTreeViewItem.h"

UAreaTreeViewItem::UAreaTreeViewItem() : Super()
{
}

void UAreaTreeViewItem::AddChild(UTreeViewItem* Child)
{
	if (Child->IsA(UAreaTreeViewItem::StaticClass()))
	{
		Children.Add(Child);
	}
	else
	{
		// Handle the error - the child is not a UAreaTreeViewItem

		// The error can be handled in many ways. For example, you can throw an exception, or you can log the error and ignore the child.
		// In this case, we will log the error and ignore the child.
		UE_LOG(LogTemp, Error, TEXT("UAreaTreeViewItem::AddChild - Child is not a UAreaTreeViewItem."));

		// print log to screen
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("UAreaTreeViewItem::AddChild - Child is not a UAreaTreeViewItem.")));

	}
}
