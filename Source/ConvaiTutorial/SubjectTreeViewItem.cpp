// Fill out your copyright notice in the Description page of Project Settings.


#include "SubjectTreeViewItem.h"

USubjectTreeViewItem::USubjectTreeViewItem()
{
}

void USubjectTreeViewItem::AddChild(UTreeViewItem* Child)
{
	if (Child->IsA(USubjectTreeViewItem::StaticClass()))
	{
		Children.Add(Child);
	}
	else
	{
		// Handle the error - the child is not a USectionTreeViewItem.

		// The error can be handled in many ways. For example, you can throw an exception, or you can log the error and ignore the child.
		// In this case, we will log the error and ignore the child.
		UE_LOG(LogTemp, Error, TEXT("USubjectTreeViewItem::AddChild - Child is not a USubjectTreeViewItem."));

		// print log to screen
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("USubjectTreeViewItem::AddChild - Child is not a USubjectTreeViewItem.")));
	}
}



