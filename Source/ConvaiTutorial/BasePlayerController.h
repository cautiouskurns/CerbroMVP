// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopicWidget.h"
#include "SectionWidget.h"
#include "GraphManagement/NodeActorBase.h"
#include "InteractWidget.h"
#include "BaseGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "SubTopicWidget.h"
#include "HUDWidgetTest.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightMouseClickedSignature);

UCLASS()
class CONVAITUTORIAL_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	void SetupInputComponent();


	UPROPERTY(EditAnywhere, Category = "Camera")
	AActor* CentralActor;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	TArray<FTopic> TopicArray;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	TArray<FSubtopic> SubtopicDataArray;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	USectionWidget* SectionWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UTopicWidget* TopicWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UHUDWidgetTest* HUDTestWidgetReference;
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
		USectionWidget* CreateSectionWidget(const TArray<FTopic>& BlueprintTopicArray, const FSectionStruct& SectionData,
			TSubclassOf<UUserWidget> SectionWidgetClass, TSubclassOf<UUserWidget> TopicWidgetClass, 
			TSubclassOf<UUserWidget> SubtopicWidgetClass, UHUDWidgetTest* InHUDTestWidget);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	TArray<FSubtopic> CreateTopicWidgets(const TArray<FTopic>& BlueprintTopicArray, USectionWidget* InSectionWidget, 
		TSubclassOf<UUserWidget> TopicWidgetClass, TSubclassOf<UUserWidget> SubtopicWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateSubTopicWidgets(const TArray<FSubtopic>& SubTopics, UTopicWidget* TopicWidget,
		TSubclassOf<UUserWidget> SubtopicWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void RemoveAllChildrenFromWidget(UUserWidget* TargetWidget);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void MoveCameraToNode(ANodeActorBase* Node);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void OnRightMouseClick();

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	bool bMovingToNode;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	FVector TargetPosition;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	FRotator TargetOrientation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UPROPERTY()
	UInteractWidget* InteractWidget;

public:
	void SetInteractWidget(UInteractWidget* NewWidget);


private:
	FString LastClickedNodeContent;  // Declare a member variable to store the content
	FString LastClickedNodeTitle;  // Declare a member variable to store the title


public:
	// Getter function to retrieve the content
	UFUNCTION(BlueprintPure, Category = "Node Content")
	FString GetLastClickedNodeContent() const { return LastClickedNodeContent; }

	// Getter function to retrieve the content
	UFUNCTION(BlueprintPure, Category = "Node Content")
	FString GetLastClickedNodeTitle() const { return LastClickedNodeTitle; }

public:
	// We want this public so our UI can access it to subscribe to it
	// Also adding BlueprintAssignable makes it accessible by blueprints
	UPROPERTY(BlueprintAssignable)
	FOnRightMouseClickedSignature OnRightMouseClickedDelegate;


	UFUNCTION(BlueprintCallable, Category = "Data")
	void TestDataTable(FName RowName);

public:



	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateDirectoryHierarchyWidgets(const TArray<FFieldStruct>& FieldDataArray, TSubclassOf<UFieldWidget> FieldWidgetClass, TSubclassOf<UAreaWidget> AreaWidgetClass, TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass, UDirectoryWidget* MainUIDirectory);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateAreaWidgets(const TArray<FAreaStruct>& AreaDataArray, UFieldWidget* ParentWidget, TSubclassOf<UAreaWidget> AreaWidgetClass, TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateSubjectWidgets(const TArray<FHierarchySubjectStruct>& SubjectDataArray, UAreaWidget* ParentWidget, TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateResourceWidgets(const TArray<FResourceStruct>& ResourceDataArray, UHierarchySubjectWidget* ParentWidget, TSubclassOf<UResourceWidget> ResourceWidgetClass);



	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UDirectoryWidget* DirectoryWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UFieldWidget* FieldWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UAreaWidget* AreaWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UHierarchySubjectWidget* HierarchySubjectWidgetReference;
};
