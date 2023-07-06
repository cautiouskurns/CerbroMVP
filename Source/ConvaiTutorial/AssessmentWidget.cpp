// Fill out your copyright notice in the Description page of Project Settings.


#include "AssessmentWidget.h"
#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"


FTest UAssessmentWidget::GetCurrentQuestion()
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GameInstance) return FTest();

    TArray<FSubjectStruct> GameInstanceSubjectDataArray = GameInstance->SubjectDataArray;

	// If Free selection is active, randomize the QuestionIndex before getting the question.
	if (QuestionSelector.RandomizationLevel == 0)
	{
		if (QuestionSelector.SubjectIndex < GameInstanceSubjectDataArray.Num() &&
			QuestionSelector.SectionIndex < GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() &&
			QuestionSelector.TopicIndex < GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() &&
			QuestionSelector.SubTopicIndex < GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num())
		{
			QuestionSelector.QuestionIndex = FMath::RandRange(0, GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num() - 1);
		}
	}

	if (QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= GameInstanceSubjectDataArray.Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() ||
		QuestionSelector.TopicIndex < 0 || QuestionSelector.TopicIndex >= GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() ||
		QuestionSelector.SubTopicIndex < 0 || QuestionSelector.SubTopicIndex >= GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num() ||
		QuestionSelector.QuestionIndex < 0 || QuestionSelector.QuestionIndex >= GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num())
	{
		// One or more indices are not set or out of bounds. Handle this error case as appropriate for your game.
		return FTest();
	}

    return GameInstanceSubjectDataArray[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions[QuestionSelector.QuestionIndex];
}



void UAssessmentWidget::ResetIndices()
{
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
	TArray<FSubjectStruct>* DataArray = GameInstance ? &GameInstance->SubjectDataArray : nullptr;
	if (!DataArray) return;

	switch (Level)
	{
	case 0:  // Free selection
		// Index setting should be done in the combobox selection change event, not here.
		break;
	case 1:  // Subject
		QuestionSelector.SubjectIndex = Index;
		break;
	case 2:  // Section
		QuestionSelector.SectionIndex = Index;
		break;
	case 3:  // Topic
		QuestionSelector.TopicIndex = Index;
		break;
	case 4:  // Subtopic
		QuestionSelector.SubTopicIndex = Index;
		break;
	//case 5:  // Question
	//	QuestionSelector.QuestionIndex = Index;
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
	TArray<FSubjectStruct>* DataArray = GameInstance ? &GameInstance->SubjectDataArray : nullptr;
	if (!DataArray) return;

	switch (QuestionSelector.RandomizationLevel)
	{
	case 0:  // Free selection
		break;
	case 1:  // Randomize Subject
		QuestionSelector.SubjectIndex = FMath::RandRange(0, DataArray->Num() - 1);
		// fall through to randomize the next levels as well

	case 2:  // Randomize Section
		if (QuestionSelector.SubjectIndex >= 0 && QuestionSelector.SubjectIndex < DataArray->Num())
		{
			QuestionSelector.SectionIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() - 1);
			// fall through to randomize the next levels as well
		}

	case 3:  // Randomize Topic
		if (QuestionSelector.SectionIndex >= 0 && QuestionSelector.SectionIndex < (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num())
		{
			QuestionSelector.TopicIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() - 1);
			// fall through to randomize the next levels as well
		}

	case 4:  // Randomize Subtopic
		if (QuestionSelector.TopicIndex >= 0 && QuestionSelector.TopicIndex < (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num())
		{
			QuestionSelector.SubTopicIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num() - 1);
			// fall through to randomize the next levels as well
		}

	case 5:  // Randomize Question
		if (QuestionSelector.SubTopicIndex >= 0 && QuestionSelector.SubTopicIndex < (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num())
		{
			QuestionSelector.QuestionIndex = FMath::RandRange(0, (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Questions.Num() - 1);
		}

	default:
		break;
	}
}

FText UAssessmentWidget::GetSubjectName() const
{
	// Get DataArray from GameInstance
	UWorld* World = GetWorld();
	UBaseGameInstance* GameInstance = World ? Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(World)) : nullptr;
	TArray<FSubjectStruct>* DataArray = GameInstance ? &GameInstance->SubjectDataArray : nullptr;
	if (!DataArray || QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= DataArray->Num()) return FText::GetEmpty();

	// Retrieve and return the subject name
	FString SubjectName = (*DataArray)[QuestionSelector.SubjectIndex].SubjectName;
	return FText::FromString(SubjectName);
}

FText UAssessmentWidget::GetSectionName() const
{
	// Get DataArray from GameInstance
	UWorld* World = GetWorld();
	UBaseGameInstance* GameInstance = World ? Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(World)) : nullptr;
	TArray<FSubjectStruct>* DataArray = GameInstance ? &GameInstance->SubjectDataArray : nullptr;
	if (!DataArray || QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= DataArray->Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num()) return FText::GetEmpty();

	// Retrieve and return the section name
	FString SectionName = (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].SectionName;
	return FText::FromString(SectionName);
}

FText UAssessmentWidget::GetTopicName() const
{
	// Get DataArray from GameInstance
	UWorld* World = GetWorld();
	UBaseGameInstance* GameInstance = World ? Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(World)) : nullptr;
	TArray<FSubjectStruct>* DataArray = GameInstance ? &GameInstance->SubjectDataArray : nullptr;

	if (!DataArray || QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= DataArray->Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() ||
		QuestionSelector.TopicIndex < 0 || QuestionSelector.TopicIndex >= (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num()) return FText::GetEmpty();

	// Retrieve and return the topic name
	FString TopicName = (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Title;
	return FText::FromString(TopicName);
}

FText UAssessmentWidget::GetSubTopicName() const
{
	// Get DataArray from GameInstance
	UWorld* World = GetWorld();
	UBaseGameInstance* GameInstance = World ? Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(World)) : nullptr;
	TArray<FSubjectStruct>* DataArray = GameInstance ? &GameInstance->SubjectDataArray : nullptr;

	if (!DataArray || QuestionSelector.SubjectIndex < 0 || QuestionSelector.SubjectIndex >= DataArray->Num() ||
		QuestionSelector.SectionIndex < 0 || QuestionSelector.SectionIndex >= (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray.Num() ||
		QuestionSelector.TopicIndex < 0 || QuestionSelector.TopicIndex >= (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics.Num() ||
		QuestionSelector.SubTopicIndex < 0 || QuestionSelector.SubTopicIndex >= (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics.Num()) return FText::GetEmpty();

	// Retrieve and return the subtopic name
	FString SubTopicName = (*DataArray)[QuestionSelector.SubjectIndex].SubjectDetailsArray[QuestionSelector.SectionIndex].Topics[QuestionSelector.TopicIndex].Subtopics[QuestionSelector.SubTopicIndex].Title;
	return FText::FromString(SubTopicName);
}


