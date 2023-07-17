// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectoryHierarchyManager.h"
#include "FieldWidget.h"
#include "AreaWidget.h"
#include "SubjectWidget.h"
#include "ResourceWidget.h"
#include "DirectoryWidget.h"
#include "Engine/Engine.h"


 


//
//void UDirectoryHierarchyManager::CreateDirectoryHierarchyWidgets(
//    const TArray<FFieldStruct>& FieldDataArray,
//    TSubclassOf<UFieldWidget> FieldWidgetClass,
//    TSubclassOf<UAreaWidget> AreaWidgetClass,
//    TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass,
//    TSubclassOf<UResourceWidget> ResourceWidgetClass,
//    UDirectoryWidget* MainUIDirectory)
//{
//    DirectoryWidgetReference = MainUIDirectory;
//
//    for (const FFieldStruct& FieldData : FieldDataArray)
//    {
//        UFieldWidget* FieldWidget = CreateWidget<UFieldWidget>(GetWorld(), FieldWidgetClass);
//
//        // pritn field widget name to screen for debugging
//        FString DebugString3 = FString::Printf(TEXT("FieldWidget: %s"), *FieldWidget->GetName());
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugString3);
//
//        if (FieldWidget)
//        {
//            // Set the name of the FieldWidget
//            // print to screen for debugging 
//            FString DebugString1 = FString::Printf(TEXT("FieldWidget: %s"), *FieldWidget->GetName());
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugString1);
//
//
//            FieldWidget->SetName(FieldData.Name);
//            CreateAreaWidgets(FieldData.Areas, FieldWidget, AreaWidgetClass, SubjectWidgetClass, ResourceWidgetClass);
//
//            // Add FieldWidget to the main UI
//            if (MainUIDirectory != nullptr)
//            {
//                MainUIDirectory->AddFieldWidget(FieldWidget);
//
//                // print to screen for debugging
//               /* FString DebugString = FString::Printf(TEXT("FieldWidget: %s"), *FieldWidget->GetName());
//                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugString);*/
//            }
//
//            // Check if the cast was successful
//            if (DirectoryWidgetReference)
//            {
//                DirectoryWidgetReference->AddFieldWidget(FieldWidget);
//
//                //print to screen for debugging
//               /* FString DebugString = FString::Printf(TEXT("FieldWidget: %s"), *FieldWidget->GetName());
//                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugString);*/
//            }
//        }
//    }
//
//    // print to screen for debugging
//    FString DebugString = FString::Printf(TEXT("FieldWidged funciton called"));
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugString);
//}
//
//
//void UDirectoryHierarchyManager::CreateAreaWidgets(
//    const TArray<FAreaStruct>& AreaDataArray,
//    UFieldWidget* ParentWidget,
//    TSubclassOf<UAreaWidget> AreaWidgetClass,
//    TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass,
//    TSubclassOf<UResourceWidget> ResourceWidgetClass)
//{
//    FieldWidgetReference = ParentWidget;
//
//    for (const FAreaStruct& AreaData : AreaDataArray)
//    {
//        UAreaWidget* AreaWidget = CreateWidget<UAreaWidget>(GetWorld(), AreaWidgetClass);
//        if (AreaWidget)
//        {
//            AreaWidget->SetName(AreaData.Name);
//            CreateSubjectWidgets(AreaData.Subjects, AreaWidget, SubjectWidgetClass, ResourceWidgetClass);
//            ParentWidget->AddChildWidget(AreaWidget);
//
//            if (FieldWidgetReference)
//            {
//                FieldWidgetReference->AddAreaWidget(AreaWidget);
//            }
//        }
//    }
//}
//
//
//void UDirectoryHierarchyManager::CreateSubjectWidgets(
//    const TArray<FHierarchySubjectStruct>& SubjectDataArray,
//    UAreaWidget* ParentWidget,
//    TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass,
//    TSubclassOf<UResourceWidget> ResourceWidgetClass)
//{
//    AreaWidgetReference = ParentWidget;
//
//    for (const FHierarchySubjectStruct& SubjectData : SubjectDataArray)
//    {
//        UHierarchySubjectWidget* SubjectWidget = CreateWidget<UHierarchySubjectWidget>(GetWorld(), SubjectWidgetClass);
//        if (SubjectWidget)
//        {
//            SubjectWidget->SetName(SubjectData.Name);
//            CreateResourceWidgets(SubjectData.Resources, SubjectWidget, ResourceWidgetClass);
//            ParentWidget->AddChildWidget(SubjectWidget);
//
//            if (AreaWidgetReference)
//            {
//                AreaWidgetReference->AddHierarchySubjectWidget(SubjectWidget);
//            }
//        }
//    }
//}
//
//void UDirectoryHierarchyManager::CreateResourceWidgets(
//    const TArray<FResourceStruct>& ResourceDataArray,
//    UHierarchySubjectWidget* ParentWidget,
//    TSubclassOf<UResourceWidget> ResourceWidgetClass)
//{
//    HierarchySubjectWidgetReference = ParentWidget;
//
//    for (const FResourceStruct& ResourceData : ResourceDataArray)
//    {
//        UResourceWidget* ResourceWidget = CreateWidget<UResourceWidget>(GetWorld(), ResourceWidgetClass);
//        if (ResourceWidget)
//        {
//            ResourceWidget->SetName(ResourceData.Name);
//            ParentWidget->AddChildWidget(ResourceWidget);
//        }
//    }
//}

