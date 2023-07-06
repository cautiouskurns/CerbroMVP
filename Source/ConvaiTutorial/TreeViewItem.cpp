// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeViewItem.h"


void UTreeViewItem::AddChild(UTreeViewItem* Child)
{
    if (Child)
    {
        Children.Add(Child);
        Child->Parent = this;
        UE_LOG(LogTemp, Warning, TEXT("AddChild called with child: %s"), *Child->GetName());

    }

}

void UTreeViewItem::RemoveChild(UTreeViewItem* Child)
{
    if (Child)
    {
        Children.Remove(Child);
        Child->Parent = nullptr;
    }
}

void UTreeViewItem::SetName(FString NewName)
{
    Name = NewName;
    UE_LOG(LogTemp, Warning, TEXT("SetName called with name: %s"), *NewName);
}
