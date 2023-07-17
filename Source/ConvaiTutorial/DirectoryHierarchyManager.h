// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FieldWidget.h"
#include "AreaWidget.h"
#include "HierarchySubjectWidget.h"
#include "ResourceWidget.h"
#include "DirectoryWidget.h"
#include "DirectoryHierarchyManager.generated.h"




//USTRUCT(BlueprintType)
//struct FResourceStruct
//{
//    GENERATED_BODY()
//
//public:
//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    FString Name;
//};
//
//USTRUCT(BlueprintType)
//struct FHierarchySubjectStruct
//{
//    GENERATED_BODY()
//
//public:
//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    FString Name;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    TArray<FResourceStruct> Resources;
//};

//USTRUCT(BlueprintType)
//struct FAreaStruct
//{
//    GENERATED_BODY()
//
//public:
//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    FString Name;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    TArray<FHierarchySubjectStruct> Subjects;
//};
//
//USTRUCT(BlueprintType)
//struct FFieldStruct
//{
//    GENERATED_BODY()
//
//public:
//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    FString Name;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    TArray<FAreaStruct> Areas;
//};



UCLASS()
class CONVAITUTORIAL_API UDirectoryHierarchyManager : public UObject
{
	GENERATED_BODY()

public:



// UFUNCTION(BlueprintCallable, Category = "Widgets")
//void CreateDirectoryHierarchyWidgets(const TArray<FFieldStruct>& FieldDataArray, TSubclassOf<UFieldWidget> FieldWidgetClass, TSubclassOf<UAreaWidget> AreaWidgetClass, TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass, UDirectoryWidget* MainUIDirectory);
//
//UFUNCTION(BlueprintCallable, Category = "Widgets")
//void CreateAreaWidgets(const TArray<FAreaStruct>& AreaDataArray, UFieldWidget* ParentWidget, TSubclassOf<UAreaWidget> AreaWidgetClass, TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass);
//
//UFUNCTION(BlueprintCallable, Category = "Widgets")
//void CreateSubjectWidgets(const TArray<FHierarchySubjectStruct>& SubjectDataArray, UAreaWidget* ParentWidget, TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass);
//
//UFUNCTION(BlueprintCallable, Category = "Widgets")
//void CreateResourceWidgets(const TArray<FResourceStruct>& ResourceDataArray, UHierarchySubjectWidget* ParentWidget, TSubclassOf<UResourceWidget> ResourceWidgetClass);
//
//
//
//UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
//UDirectoryWidget* DirectoryWidgetReference;
//
//UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
//UFieldWidget* FieldWidgetReference;
//
//UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
//UAreaWidget* AreaWidgetReference;
//
//UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
//UHierarchySubjectWidget* HierarchySubjectWidgetReference;
//




};
	
