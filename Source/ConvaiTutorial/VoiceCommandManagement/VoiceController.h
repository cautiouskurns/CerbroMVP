// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"


#include "VoiceController.generated.h"


/**
 * 
 */
class ABasePlayerController;  // forward declaration

UCLASS(Blueprintable)
class CONVAITUTORIAL_API UVoiceController : public UObject
{
	GENERATED_BODY()

public:
    void Init(UBaseGameInstance *InGameInstance);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FString PrintContentForVoicePrompt(FString VoicePrompt);
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	FSubjectStruct FindSubjectByVocalPrompt(FString SubjectName);
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void RetrieveSectionsForSubject(FString SubjectName);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void RetrieveTopicsForSection(const FSectionStruct& SectionData);
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void RetrieveSubtopicsForTopic(const FTopic& TopicData);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void ClearContentForVoicePrompt(FString VoicePrompt);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	ACharacter* GetPlayerCharacter();

public:
	// UFUNCTION(BlueprintImplementableEvent)
	// void UpdateTextWidget(const FString& Text);

	// UFUNCTION(BlueprintNativeEvent)
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void UpdateTextWidget(const FString& Text);
	// virtual void UpdateTextWidget_Implementation(const FString& Text);

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
	ABasePlayerController* PlayerControllerRef;

public:
    UBaseGameInstance* GameInstance; // Here is where you declare GameInstance

};
