// Fill out your copyright notice in the Description page of Project Settings.


#include "DataProvider.h"


void UDataProvider::ConstructHierarchy()
{
    // Create the root item
    UTreeViewItem* Root = NewObject<UTreeViewItem>(this);
    Root->SetName("Root");

    // Create a child item
    UTreeViewItem* Child1 = NewObject<UTreeViewItem>(this);
    Child1->SetName("Child1");

    // Add the child to the root
    Root->AddChild(Child1);

    // Add the root item to the RootItems array
    RootItems.Add(Root);

    UE_LOG(LogTemp, Warning, TEXT("ConstructHierarchy called"));
    UE_LOG(LogTemp, Warning, TEXT("GetRootItems called, returning %d items"), RootItems.Num());

}

TArray<UTreeViewItem*> UDataProvider::GetRootItems()
{
	return RootItems;
}

TArray<UTreeViewItem*> UDataProvider::GetChildrenOfItem(UTreeViewItem* Item)
{
    return Item ? Item->Children : TArray<UTreeViewItem*>();
}

