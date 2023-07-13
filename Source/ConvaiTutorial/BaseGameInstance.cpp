// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "ReadWriteJsonFile.h"
#include "Json.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include <Components/TreeView.h>
#include "JsonObjectConverter.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Engine/DataTable.h"
#include "FolderWidget.h"
#include "DataProvider.h"
#include "AssessmentMetricsCalculator.h"

UBaseGameInstance::UBaseGameInstance()
{
    //UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
}

void UBaseGameInstance::Init()
{
    Super::Init();

    // Create an instance of UDataProvider
    DataProvider = NewObject<UDataProvider>(this);

    // Call the ConstructHierarchy function
    DataProvider->ConstructHierarchy();

    // Store the DataProvider in a property if you need to access it later
    this->DataProvider = DataProvider;
}


void UBaseGameInstance::InitializeSubjectDataArray()
{

}


//int32 UBaseGameInstance::UpdateRandomQuestionTimesTested(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex)
//{
//    FSubjectStruct& SelectedSubject = SubjectDataArray[SubjectIndex];
//
//    if (SelectedSubject.SubjectDetailsArray.Num() > 0) // Check if there are any sections
//    {
//        FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
//
//        if (SelectedSection.Topics.Num() > 0) // Check if there are any topics in the selected section
//        {
//            FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
//
//            if (SelectedTopic.Subtopics.Num() > 0) // Check if there are any subtopics in the selected topic
//            {
//                FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
//
//                if (SelectedSubtopic.Questions.Num() > 0) // Check if there are any questions in the selected subtopic
//                {
//                    FTest& SelectedQuestion = SelectedSubtopic.Questions[QuestionIndex];
//
//                    // Increment the TimesTested property of the selected question
//                    SelectedQuestion.TimesTested++;
//
//                    // Return the updated TimesTested value
//                    return SelectedQuestion.TimesTested;
//                }
//            }
//        }
//    }
//
//    // Return -1 if any of the indices are invalid
//    return -1;
//}

int32 UBaseGameInstance::UpdateRandomQuestionTimesTested(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex)
{
    UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
    return AssessmentMetricsCalculator->UpdateRandomQuestionTimesTested(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionIndex, SubjectDataArray);
}

int32 UBaseGameInstance::UpdateTimesCorrect(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer)
{
    UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
    return AssessmentMetricsCalculator->UpdateTimesCorrect(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionIndex, SelectedAnswer, SubjectDataArray);
}

int32 UBaseGameInstance::CalculateTimesAskedForSubtopicIR(const FString& SubtopicTitle)
{
    UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
    return AssessmentMetricsCalculator->CalculateTimesAskedForSubtopicIR(SubtopicTitle, SubjectDataArray);
}

int32 UBaseGameInstance::CalculateTimesAskedForQuestionIR(const FString& QuestionText)
{
    UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
    return AssessmentMetricsCalculator->CalculateTimesAskedForQuestionIR(QuestionText, SubjectDataArray);
}

int32 UBaseGameInstance::CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle)
{
	UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
	return AssessmentMetricsCalculator->CalculateTimesCorrectForSubtopicIR(SubtopicTitle, SubjectDataArray);
}


FTest UBaseGameInstance::UpdateTimesTestedAndCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, const FString& SelectedAnswer)
{
    UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
    return AssessmentMetricsCalculator->UpdateTimesTestedAndCorrectForQuestion( SubjectIndex,  SectionIndex,  TopicIndex,  SubtopicIndex,  QuestionText,  SelectedAnswer, SubjectDataArray);
}


FString UBaseGameInstance::SubmitAnswer(const FString& AnswerText)
{
    if (AssessmentMetricsCalculatorGlobal == nullptr)
    {
        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
    }
    AssessmentMetricsCalculatorGlobal->SubmitAnswer(AnswerText);

    return AnswerText;
}

FTest UBaseGameInstance::UpdateAnswerStatus(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    if (AssessmentMetricsCalculatorGlobal == nullptr)
    {
        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
    }
    return AssessmentMetricsCalculatorGlobal->UpdateAnswerStatus(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, SubjectDataArray);

}


int32 UBaseGameInstance::GetTimesTestedForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    if (AssessmentMetricsCalculatorGlobal == nullptr)
    {
        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
    }
    return AssessmentMetricsCalculatorGlobal->GetTimesTestedForQuestion(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, SubjectDataArray);
}

// New function to get the number of times a specific question has been answered correctly
int32 UBaseGameInstance::GetTimesCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    if (AssessmentMetricsCalculatorGlobal == nullptr)
    {
        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
    }
    return AssessmentMetricsCalculatorGlobal->GetTimesCorrectForQuestion(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, SubjectDataArray);
}





FSubjectStruct UBaseGameInstance::LoadJsonFromFile(FString FilePath)
{
    FString JsonContent;
    if (!FFileHelper::LoadFileToString(JsonContent, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
        // Return an empty struct on failure
        return FSubjectStruct();
    }

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse the JSON in file: %s"), *FilePath);
        // Return an empty struct on failure
        return FSubjectStruct();
    }

    FSubjectStruct LoadedStruct;

    if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &LoadedStruct, 0, 0))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to convert JSON to struct: %s"), *FilePath);
        // Return an empty struct on failure
        return FSubjectStruct();
    }

    // If everything goes well, return the populated struct
    return LoadedStruct;
}




