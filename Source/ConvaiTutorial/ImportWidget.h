// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Engine/GameInstance.h"
#include "ImportWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UImportWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "File Operations")
	FString OpenDialogForFile();

	UFUNCTION(BlueprintCallable, Category = "File")
	FString LoadJsonAsString(FString FilePath);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	FString SelectedFilePath;

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	bool UpdateSubjectName(const FString& SubjectName, const FString& NewSubjectName);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void AddSectionToSubject(FString SubjectName, FSectionStruct NewSection);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	bool UpdateSectionName(const FString& SubjectName, const FString& SectionName, const FString& NewSectionName);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void AddTopicToSectionInSubject(FString SubjectName, FString SectionName, FTopic NewTopic);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	bool UpdateTopicName(const FString& SubjectName, const FString& SectionName, const FString& TopicName, const FString& NewTopicName);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void AddSubtopicToTopicInSection(FString SubjectName, FString SectionName, FString TopicName, FSubtopic NewSubtopic);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void AddOrUpdateSubtopicInTopicInSection(FString SubjectName, FString SectionName, FString TopicName, FSubtopic NewSubtopic);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	bool AddSubtopicToTopic(const FString& SubjectName, const FString& SectionName, const FString& TopicName, const FString& NewSubtopicName, const FString& NewSubtopicContent);

	
};
