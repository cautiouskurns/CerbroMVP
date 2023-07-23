// Fill out your copyright notice in the Description page of Project Settings.


#include "AssessmentWidget.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"


#include "Kismet/GameplayStatics.h"
#include <Components/ComboBoxString.h>


void UAssessmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AnswerButtons.Add(Answer1Button);
	AnswerButtons.Add(Answer2Button);
	AnswerButtons.Add(Answer3Button);
	AnswerButtons.Add(Answer4Button);
}


FTest UAssessmentWidget::GetCurrentQuestion()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance) return FTest();

	TArray<FFieldStruct> GameInstanceFieldDataArray = GameInstance->FieldDataArray;

	// If Free selection is active, randomize the QuestionIndex before getting the question.
	if (QuestionSelector.RandomizationLevel == 0)
	{
		if (QuestionSelector.FieldIndex < GameInstanceFieldDataArray.Num() &&
			QuestionSelector.AreaIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas.Num() &&
			QuestionSelector.SubjectGroupIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() &&
			QuestionSelector.SubjectIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() &&
			QuestionSelector.SectionIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() &&
			QuestionSelector.TopicIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() &&
			QuestionSelector.SubTopicIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num())
		{
			QuestionSelector.QuestionIndex = FMath::RandRange(0, GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num() - 1);

			if (QuestionSelector.QuestionIndex < 0 || QuestionSelector.QuestionIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num())
			{
				// One or more indices are not set or out of bounds. Handle this error case as appropriate for your game.
				return FTest();
			}
		}
	}
	else if (QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstanceFieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas.Num() ||
		QuestionSelector.SubjectGroupIndex < 0 || QuestionSelector.SubjectGroupIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() ||
		QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() ||
		QuestionSelector.TopicIndex < 0 || QuestionSelector.TopicIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() ||
		QuestionSelector.SubTopicIndex < 0 || QuestionSelector.SubTopicIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num() ||
		QuestionSelector.QuestionIndex < 0 || QuestionSelector.QuestionIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num())
	{
		// One or more indices are not set or out of bounds. Handle this error case as appropriate for your game.
		return FTest();
	}

	return GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions[QuestionSelector.QuestionIndex];
}



FString UAssessmentWidget::GetCurrentQuestionContent()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance) return FString();

	TArray<FFieldStruct> GameInstanceFieldDataArray = GameInstance->FieldDataArray;

	// If Free selection is active, randomize the QuestionIndex before getting the question.
	if (QuestionSelector.RandomizationLevel == 0)
	{
		if (QuestionSelector.FieldIndex < GameInstanceFieldDataArray.Num() &&
			QuestionSelector.AreaIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas.Num() &&
			QuestionSelector.SubjectGroupIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() &&
			QuestionSelector.SubjectIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() &&
			QuestionSelector.SectionIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() &&
			QuestionSelector.TopicIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() &&
			QuestionSelector.SubTopicIndex < GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num())
		{
			QuestionSelector.QuestionIndex = FMath::RandRange(0, GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num() - 1);

			if (QuestionSelector.QuestionIndex < 0 || QuestionSelector.QuestionIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num())
			{
				// One or more indices are not set or out of bounds. Handle this error case as appropriate for your game.
				return FString();
			}
		}
	}
	else if (QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstanceFieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas.Num() ||
		QuestionSelector.SubjectGroupIndex < 0 || QuestionSelector.SubjectGroupIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() ||
		QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() ||
		QuestionSelector.TopicIndex < 0 || QuestionSelector.TopicIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() ||
		QuestionSelector.SubTopicIndex < 0 || QuestionSelector.SubTopicIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num() ||
		QuestionSelector.QuestionIndex < 0 || QuestionSelector.QuestionIndex >= GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num())
	{
		// One or more indices are not set or out of bounds. Handle this error case as appropriate for your game.
		return FString();
	}

	return GameInstanceFieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Content;
}




void UAssessmentWidget::ResetIndices()
{
	QuestionSelector.FieldIndex = -1;  
	QuestionSelector.AreaIndex= -1;  
	QuestionSelector.SubjectGroupIndex = -1;
	QuestionSelector.SubjectIndex = -1;
	QuestionSelector.SectionIndex = -1;
	QuestionSelector.TopicIndex = -1;
	QuestionSelector.SubTopicIndex = -1;
	QuestionSelector.QuestionIndex = -1;
}

void UAssessmentWidget::SetFieldIndex(int32 Index)
{
	QuestionSelector.FieldIndex = Index;
	QuestionSelector.AreaIndex = -1;
	QuestionSelector.SubjectGroupIndex = -1;
	QuestionSelector.SubjectIndex = -1;
	QuestionSelector.SectionIndex = -1;
	QuestionSelector.TopicIndex = -1;
	QuestionSelector.SubTopicIndex = -1;
	QuestionSelector.QuestionIndex = -1;
}

void UAssessmentWidget::SetAreaIndex(int32 Index)
{
	QuestionSelector.AreaIndex = Index;
	QuestionSelector.SubjectGroupIndex = -1;
	QuestionSelector.SubjectIndex = -1;
	QuestionSelector.SectionIndex = -1;
	QuestionSelector.TopicIndex = -1;
	QuestionSelector.SubTopicIndex = -1;
	QuestionSelector.QuestionIndex = -1;
}

void UAssessmentWidget::SetSubjectGroupIndex(int32 Index)
{
	QuestionSelector.SubjectGroupIndex = Index;
	QuestionSelector.SubjectIndex = -1;
	QuestionSelector.SectionIndex = -1;  
	QuestionSelector.TopicIndex = -1;
	QuestionSelector.SubTopicIndex = -1;
	QuestionSelector.QuestionIndex = -1;
}

void UAssessmentWidget::SetSubjectIndex(int32 Index)
{
	QuestionSelector.SubjectIndex = Index;
	QuestionSelector.SectionIndex = -1;  // Reset other indices
	QuestionSelector.TopicIndex = -1;
	QuestionSelector.SubTopicIndex = -1;
	QuestionSelector.QuestionIndex = -1;
}

void UAssessmentWidget::SetSectionIndex(int32 Index)
{
	QuestionSelector.SectionIndex = Index;
	QuestionSelector.TopicIndex = -1;  // Reset other indices
	QuestionSelector.SubTopicIndex = -1;
	QuestionSelector.QuestionIndex = -1;
}

void UAssessmentWidget::SetTopicIndex(int32 Index)
{
	QuestionSelector.TopicIndex = Index;
	QuestionSelector.SubTopicIndex = -1;
	QuestionSelector.QuestionIndex = -1;
}

void UAssessmentWidget::SetSubTopicIndex(int32 Index)
{
	QuestionSelector.SubTopicIndex = Index;
	QuestionSelector.QuestionIndex = -1;
}



void UAssessmentWidget::SetSelectionIndices(int32 Level, int32 Index)
{
	// Validate the input. If it's out of range for the selected level, you might want to handle it as an error.
	// Get DataArray from GameInstance
	UWorld* World = GetWorld();
	UBaseGameInstance* GameInstance = World ? Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(World)) : nullptr;
	TArray<FFieldStruct>* DataArray = GameInstance ? &GameInstance->FieldDataArray : nullptr;
	if (!DataArray) return;

	switch (Level)
	{
	case 0:  // Free selection
		// Index setting should be done in the combobox selection change event, not here.
		break;
	case 1:  // Field
		QuestionSelector.FieldIndex = Index;
		break;
	case 2:  // Area
		QuestionSelector.AreaIndex = Index;
		break;
	case 3:  // Subject Group
		QuestionSelector.SubjectGroupIndex = Index;
		break;
	case 4:  // Subject
		QuestionSelector.SubjectIndex = Index;
		break;
	case 5:  // Section
		QuestionSelector.SectionIndex = Index;
		break;
	case 6:  // Topic
		QuestionSelector.TopicIndex = Index;
		break;
	case 7:  // Subtopic
		QuestionSelector.SubTopicIndex = Index;
		break;
	default:
		// Handle this as an error. Perhaps print a message to the log.
		UE_LOG(LogTemp, Error, TEXT("Invalid selection level in SetSelectionIndices: %d"), Level);
		break;
	}
}


void UAssessmentWidget::SetRandomizationLevel(int32 NewRandomizationLevel)
{
	QuestionSelector.RandomizationLevel = NewRandomizationLevel;
}


void UAssessmentWidget::SetSelectionRandomizationLevel()
{
	// Get DataArray from GameInstance
	UWorld* World = GetWorld();
	UBaseGameInstance* GameInstance = World ? Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(World)) : nullptr;
	TArray<FFieldStruct>* DataArray = GameInstance ? &GameInstance->FieldDataArray : nullptr;
	if (!DataArray) return;

	switch (QuestionSelector.RandomizationLevel)
	{
	case 0:  // Free selection
		break;
	case 1:  // Randomize Field
		QuestionSelector.FieldIndex = FMath::RandRange(0, DataArray->Num() - 1);
		// fall through to randomize the next levels as well
	case 2:  // Randomize Area
		if (QuestionSelector.FieldIndex >= 0 && QuestionSelector.FieldIndex < DataArray->Num())
		{
			QuestionSelector.AreaIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.FieldIndex].Areas.Num() - 1);
			// fall through to randomize the next levels as well
		}
	case 3:  // Randomize SubjectGroup
		if (QuestionSelector.AreaIndex >= 0 && QuestionSelector.AreaIndex < (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num())
		{
			QuestionSelector.SubjectGroupIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() - 1);
			// fall through to randomize the next levels as well
		}
	case 4:  // Randomize Subject
		if (QuestionSelector.SubjectGroupIndex >= 0 && QuestionSelector.SubjectGroupIndex < (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num())
		{
			QuestionSelector.SubjectIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() - 1);
			// fall through to randomize the next levels as well
		}
	case 5:  // Randomize Section
		if (QuestionSelector.SubjectIndex >= 0 && QuestionSelector.SubjectIndex < (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num())
		{
			QuestionSelector.SectionIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() - 1);
			// fall through to randomize the next levels as well
		}
	case 6:  // Randomize Topic
		if (QuestionSelector.SectionIndex >= 0 && QuestionSelector.SectionIndex < (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num())
		{
			QuestionSelector.TopicIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() - 1);
			// fall through to randomize the next levels as well
		}
	case 7:  // Randomize Subtopic
		if (QuestionSelector.TopicIndex >= 0 && QuestionSelector.TopicIndex < (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num())
		{
			QuestionSelector.SubTopicIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num() - 1);
			// fall through to randomize the next levels as well
		}
	case 8:  // Randomize Question
		if (QuestionSelector.SubTopicIndex >= 0 && QuestionSelector.SubTopicIndex < (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num())
		{
			QuestionSelector.QuestionIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num() - 1);
		}
	default:
		break;
	}
}



FText UAssessmentWidget::GetFieldName() const
{
	// Get FieldDataArray from GameInstance
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstance->FieldDataArray.Num())
		return FText::GetEmpty();

	// Retrieve and return the field name
	FString FieldName = GameInstance->FieldDataArray[QuestionSelector.FieldIndex].FieldName;
	return FText::FromString(FieldName);
}


FText UAssessmentWidget::GetAreaName() const
{
	// Get FieldDataArray from GameInstance
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstance->FieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas.Num())
		return FText::GetEmpty();

	// Retrieve and return the area name
	FString AreaName = GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].AreaName;
	return FText::FromString(AreaName);
}

FText UAssessmentWidget::GetSubjectGroupName() const
{
	// Get FieldDataArray from GameInstance
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstance->FieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas.Num() ||
		QuestionSelector.SubjectGroupIndex < 0 || QuestionSelector.SubjectGroupIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num())
		return FText::GetEmpty();

	// Retrieve and return the subject group name
	FString SubjectGroupName = GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].SubjectGroupName;
	return FText::FromString(SubjectGroupName);
}

FText UAssessmentWidget::GetSubjectName() const
{
	// Get FieldDataArray from GameInstance
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstance->FieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas.Num() ||
		QuestionSelector.SubjectGroupIndex < 0 || QuestionSelector.SubjectGroupIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() ||
		QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num())
		return FText::GetEmpty();

	// Retrieve and return the subject name
	FString SubjectName = GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectName;
	return FText::FromString(SubjectName);
}

FText UAssessmentWidget::GetSectionName() const
{
	// Get FieldDataArray from GameInstance
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstance->FieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas.Num() ||
		QuestionSelector.SubjectGroupIndex < 0 || QuestionSelector.SubjectGroupIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() ||
		QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num())
		return FText::GetEmpty();

	// Retrieve and return the section name
	FString SectionName = GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].SectionName;
	return FText::FromString(SectionName);
}

FText UAssessmentWidget::GetTopicName() const
{
	// Get FieldDataArray from GameInstance
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstance->FieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas.Num() ||
		QuestionSelector.SubjectGroupIndex < 0 || QuestionSelector.SubjectGroupIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() ||
		QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() ||
		QuestionSelector.TopicIndex < 0 || QuestionSelector.TopicIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num())
		return FText::GetEmpty();

	// Retrieve and return the topic name
	FString TopicName = GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Title;
	return FText::FromString(TopicName);
}

FText UAssessmentWidget::GetSubTopicName() const
{
	// Get FieldDataArray from GameInstance
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || QuestionSelector.FieldIndex < 0 || QuestionSelector.FieldIndex >= GameInstance->FieldDataArray.Num() ||
		QuestionSelector.AreaIndex < 0 || QuestionSelector.AreaIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas.Num() ||
		QuestionSelector.SubjectGroupIndex < 0 || QuestionSelector.SubjectGroupIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups.Num() ||
		QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects.Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() ||
		QuestionSelector.TopicIndex < 0 || QuestionSelector.TopicIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() ||
		QuestionSelector.SubTopicIndex < 0 || QuestionSelector.SubTopicIndex >= GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num())
		return FText::GetEmpty();

	// Retrieve and return the subtopic name
	FString SubTopicName = GameInstance->FieldDataArray[QuestionSelector.FieldIndex].Areas[QuestionSelector.AreaIndex].SubjectGroups[QuestionSelector.SubjectGroupIndex].Subjects[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Title;
	return FText::FromString(SubTopicName);
}




void UAssessmentWidget::PopulateFieldComboBox(UComboBoxString* ComboBox)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		// Add FieldName to combo box
		ComboBox->AddOption(FieldData.FieldName);
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}



void UAssessmentWidget::PopulateAreaComboBox(UComboBoxString* ComboBox, const FString& SelectedField)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		// Only add options for the selected field
		if (FieldData.FieldName == SelectedField)
		{
			// Loop through Areas in FieldData
			for (const FAreaStruct& AreaData : FieldData.Areas)
			{
				// Add AreaName to combo box
				ComboBox->AddOption(AreaData.AreaName);
			}

			// Found the selected field, no need to continue the loop
			break;
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}



void UAssessmentWidget::PopulateSubjectGroupComboBox(UComboBoxString* ComboBox, const FString& SelectedArea)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			// Only add options for the selected area
			if (AreaData.AreaName == SelectedArea)
			{
				// Loop through SubjectGroups in AreaData
				for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
				{
					// Add SubjectGroupName to combo box
					ComboBox->AddOption(SubjectGroupData.SubjectGroupName);
				}

				// Found the selected area, no need to continue the loop
				break;
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UAssessmentWidget::PopulateSubjectComboBox(UComboBoxString* ComboBox, const FString& SelectedSubjectGroup)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				// Only add options for the selected subject group
				if (SubjectGroupData.SubjectGroupName == SelectedSubjectGroup)
				{
					// Loop through Subjects in SubjectGroupData
					for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
					{
						// Add SubjectName to combo box
						ComboBox->AddOption(SubjectData.SubjectName);
					}

					// Found the selected subject group, no need to continue the loop
					break;
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UAssessmentWidget::PopulateSectionComboBox(UComboBoxString* ComboBox, const FString& SelectedSubject)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
				{
					// Only add options for the selected subject
					if (SubjectData.SubjectName == SelectedSubject)
					{
						// Loop through SubjectDetailsArray in SubjectData
						for (const FSectionStruct& SectionData : SubjectData.SubjectDetailsArray)
						{
							// Add SectionName to combo box
							ComboBox->AddOption(SectionData.SectionName);
						}

						// Found the selected subject, no need to continue the loop
						break;
					}
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UAssessmentWidget::PopulateTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedSection)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	bool bOptionAdded = false; // Variable to check if the option has been added

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		if (bOptionAdded) break; // Break if the option has been added

		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			if (bOptionAdded) break; // Break if the option has been added

			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				if (bOptionAdded) break; // Break if the option has been added

				for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
				{
					if (bOptionAdded) break; // Break if the option has been added

					for (const FSectionStruct& SectionData : SubjectData.SubjectDetailsArray)
					{
						// Only add options for the selected topic
						if (SectionData.SectionName == SelectedSection)
						{
							// Loop through Topics in SectionData
							for (const FTopic& TopicData : SectionData.Topics)
							{
								// Add Title to combo box
								ComboBox->AddOption(TopicData.Title);
							}

							bOptionAdded = true; // Set the variable to true

							// Found the selected topic, no need to continue the loop
							break;
						}
					}
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UAssessmentWidget::PopulateSubTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedTopic)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	bool bOptionAdded = false; // Variable to check if the option has been added

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		if (bOptionAdded) break; // Break if the option has been added

		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			if (bOptionAdded) break; // Break if the option has been added

			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				if (bOptionAdded) break; // Break if the option has been added

				for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
				{
					if (bOptionAdded) break; // Break if the option has been added

					for (const FSectionStruct& SectionData : SubjectData.SubjectDetailsArray)
					{
						if (bOptionAdded) break; // Break if the option has been added

						for (const FTopic& TopicData : SectionData.Topics)
						{
							// Only add options for the selected topic
							if (TopicData.Title == SelectedTopic)
							{
								// Loop through Subtopics in TopicData
								for (const FSubtopic& SubtopicData : TopicData.Subtopics)
								{
									// Add Title to combo box
									ComboBox->AddOption(SubtopicData.Title);
								}

								bOptionAdded = true; // Set the variable to true

								// Found the selected topic, no need to continue the loop
								break;
							}
						}
					}
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}



void UAssessmentWidget::SetQuestionAndAnswers(const FString& Question, const TArray<FString>& Answers)
{
	if (QuestionText)
	{
		QuestionText->SetText(FText::FromString(Question));
	}

	UTextBlock* AnswerTextBlocks[] = { Answer1Text, Answer2Text, Answer3Text, Answer4Text };

	for (int32 i = 0; i < Answers.Num() && i < sizeof(AnswerTextBlocks) / sizeof(UTextBlock*); ++i)
	{
		if (AnswerTextBlocks[i])
		{
			AnswerTextBlocks[i]->SetText(FText::FromString(Answers[i]));
		}
	}
}


TArray<FLinearColor> UAssessmentWidget::ColorCodeAnswers(const FString& SubmittedAnswer, const TArray<FString>& PotentialAnswers, const FString& CorrectAnswer)
{
	TArray<FLinearColor> AnswerColors;
	AnswerColors.SetNum(PotentialAnswers.Num());

	for (int32 i = 0; i < PotentialAnswers.Num(); ++i)
	{
		if (PotentialAnswers[i] == SubmittedAnswer)
		{
			AnswerColors[i] = (PotentialAnswers[i] == CorrectAnswer) ? FLinearColor::Green : FLinearColor::Red;
		}
		else
		{
			AnswerColors[i] = FLinearColor::Red;
		}
	}

	return AnswerColors;
}





