// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "Blueprint/UserWidget.h"

#include "AssessmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UAssessmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // Declare a question selector
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Questions")
    FQuestionSelector QuestionSelector;

    // Function to get the current question
    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FTest GetCurrentQuestion();

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FString GetCurrentQuestionContent();


    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void ResetIndices();

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetFieldIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetAreaIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetSubjectGroupIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetSubjectIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetSectionIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetTopicIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetSubTopicIndex(int32 Index);
    

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetSelectionIndices(int32 Level, int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetRandomizationLevel(int32 NewRandomizationLevel);

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    void SetSelectionRandomizationLevel();

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FText GetSubjectName() const;

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FText GetSectionName() const;

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FText GetTopicName() const;

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FText GetSubTopicName() const;

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FText GetSubjectGroupName() const;

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FText GetAreaName() const;

    UFUNCTION(BlueprintCallable, Category = "Widgets")
    FText GetFieldName() const;


    UFUNCTION(BlueprintCallable, Category = "ComboBox")
    void PopulateFieldComboBox(UComboBoxString* ComboBox);

    UFUNCTION(BlueprintCallable, Category = "ComboBox")
    void PopulateAreaComboBox(UComboBoxString* ComboBox, const FString& SelectedField);

    UFUNCTION(BlueprintCallable, Category = "ComboBox")
    void PopulateSubjectGroupComboBox(UComboBoxString* ComboBox, const FString& SelectedArea);

    UFUNCTION(BlueprintCallable, Category = "ComboBox")
    void PopulateSubjectComboBox(UComboBoxString* ComboBox, const FString& SelectedSubjectGroup);

    UFUNCTION(BlueprintCallable, Category = "ComboBox")
    void PopulateSectionComboBox(UComboBoxString* ComboBox, const FString& SelectedSubject);

    UFUNCTION(BlueprintCallable, Category = "ComboBox")
    void PopulateTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedSection);

    UFUNCTION(BlueprintCallable, Category = "ComboBox")
    void PopulateSubTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedTopic);

};
