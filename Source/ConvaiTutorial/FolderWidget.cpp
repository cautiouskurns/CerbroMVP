// Fill out your copyright notice in the Description page of Project Settings.


#include "FolderWidget.h"
#include "ReadWriteJsonFile.h"
#include "SubjectWidget.h"
#include "BaseGameInstance.h"
#include "Components/ListView.h"
#include "Components/TreeView.h"
#include "Components/TextBlock.h"

//void UFolderWidget::SetItem(const FTreeViewItem& Item)
//{
//    Data = Item;
//    // Assuming you have a UTextBlock in your widget that should display the name.
//    //if (NameText)
//    //{
//    //    NameText->SetText(FText::FromString(Item.Name));
//    //}
//}
//
//void UFolderWidget::AddChild(UFolderWidget* Child)
//{
//    if (Child)
//    {
//        WidgetMap.Add(Child->Data.ID, Child);
//    }
//}
//
//TArray<UObject*> UFolderWidget::GetChildren()
//{
//    TArray<UObject*> Children;
//    for (int32 ChildID : Data.ChildrenIDs)
//    {
//        UFolderWidget* ChildWidget = WidgetMap.FindRef(ChildID);
//        if (ChildWidget)
//        {
//            Children.Add(ChildWidget);
//        }
//    }
//    return Children;
//}
//
//
//void UFolderWidget::NativeConstruct()
//{
//    Super::NativeConstruct();
//
//    if (SubjectTreeView)
//    {
//        PopulateTreeView();
//    }
//}
//
//void UFolderWidget::PopulateTreeView()
//{
//    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
//    if (GameInstance)
//    {
//        GameInstance->PopulateTreeView(SubjectTreeView);
//    }
//}