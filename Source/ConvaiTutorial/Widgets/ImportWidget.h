// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Engine/GameInstance.h"
#include "ConvaiTutorial/MyHttpClient.h"

#include "ImportWidget.generated.h"


UENUM(BlueprintType)
enum class EStructLevel : uint8
{
	EL_Field,
	EL_Area,
	EL_SubjectGroup,
	EL_Subject,
	EL_Section,
	EL_Topic,
	EL_Subtopic
};

UCLASS()
class CONVAITUTORIAL_API UImportWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UImportWidget(const FObjectInitializer &ObjectInitializer);
    
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

	UFUNCTION(BlueprintCallable, Category = "Data Import")
	void AddNewElement(EStructLevel Level, const FString& FieldName, const FString& AreaName, const FString& SubjectGroupName, const FString& SubjectName, const FString& SectionName, const FString& TopicName, const FString& SubtopicName, const FString& ElementName, const FString& ElementContent);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void PopulateFieldComboBox(UComboBoxString* ComboBox);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void PopulateAreaComboBox(UComboBoxString* ComboBox, const FString& SelectedField);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void PopulateSubjectGroupComboBox(UComboBoxString* ComboBox, const FString& SelectedArea);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void PopulateSubjectComboBox(UComboBoxString* ComboBox, const FString& SelectedSubjectGroup);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void PopulateSectionComboBox(UComboBoxString* ComboBox, const FString& SelectedSubject);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void PopulateTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedSection);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
	void PopulateSubTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedTopic);

	UFUNCTION(BlueprintCallable, Category = "Update Functions")
    FString ReadFileToString(FString FilePath);

	UPROPERTY(BlueprintReadWrite, Category = "HTTP")
    AMyHttpClient* HttpClient;
};
