// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/KnowledgeStructs.h"

#include "ConvaiTutorial/GraphManagement/NodeActorBase.h"

#include "ConvaiTutorial/Widgets/TopicWidget.h"
#include "ConvaiTutorial/Widgets/SectionWidget.h"
#include "ConvaiTutorial/Widgets/InteractWidget.h"
#include "ConvaiTutorial/Widgets/SubTopicWidget.h"

#include "Blueprint/UserWidget.h"

#include "ConvaiTutorial/HUDWidgetTest.h"

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
	void RemoveAllChildrenFromDirectoryWidget(UUserWidget* TargetWidget);

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

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FSubjectStruct FindSubjectByName(FString TargetSubjectName);

	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//FString PrintContentForVoicePrompt(FString VoicePrompt);


	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//FSubjectStruct FindSubjectByVocalPrompt(FString SubjectName);

	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//void RetrieveSectionsForSubject(FString SubjectName);

	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//void RetrieveTopicsForSection(const FSectionStruct& SectionData);

	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//void RetrieveSubtopicsForTopic(const FTopic& TopicData);

	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//void ClearContentForVoicePrompt(FString VoicePrompt);




	void OnButtonClicked(UResourceWidget* ClickedWidget);

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
	void CreateAreaWidgets(const TArray<FAreaStruct>& AreaDataArray, UFieldWidget* ParentWidget, TSubclassOf<UAreaWidget> AreaWidgetClass, 
		TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass, int32 FieldIndex);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateSubjectGroupWidgets(const TArray<FSubjectGroupStruct>& SubjectGroupDataArray, UAreaWidget* ParentWidget, 
		TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass, TSubclassOf<UResourceWidget> ResourceWidgetClass, int32 FieldIndex,
		int32 AreaIndex);

	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//void CreateSubjectWidgets(const TArray<FSubjectStruct>& ResourceDataArray, UHierarchySubjectWidget* ParentWidget, TSubclassOf<UTextBlock> TextWidgetClass, 
	//	TSubclassOf<UResourceWidget> ResourceWidgetClass, int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void CreateSubjectWidgets(const TArray<FSubjectStruct>& SubjectDataArray, UHierarchySubjectWidget* ParentWidget, 
		TSubclassOf<UResourceWidget> ResourceWidgetClass, int32 FieldIndex,
		int32 AreaIndex,
		int32 SubjectGroupIndex);

	//UFUNCTION(BlueprintCallable, Category = "Widgets")
	//void CreateSectionTextBlocks(const TArray<FSectionStruct>& SectionDataArray, UHierarchySubjectWidget* ParentWidget, TSubclassOf<UTextBlock> TextWidgetClass);




	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UDirectoryWidget* DirectoryWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UFieldWidget* FieldWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UAreaWidget* AreaWidgetReference;

	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UHierarchySubjectWidget* HierarchySubjectWidgetReference;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTextWidget(const FString& Text);

	// Blueprint Implementable Events
	UFUNCTION(BlueprintImplementableEvent, Category = "Curriculum")
	void OnSectionFound(const FString& SectionText);

	UFUNCTION(BlueprintImplementableEvent, Category = "Curriculum")
	void OnTopicFound(const FString& TopicText);

	UFUNCTION(BlueprintImplementableEvent, Category = "Curriculum")
	void OnSubtopicFound(const FString& SubtopicText);

	UFUNCTION(BlueprintImplementableEvent, Category = "Voice")
	void OnClearContent();


	UPROPERTY(BlueprintReadWrite, Category = "Topic Data")
	UVoiceController* VoiceControllerInstance;
};
