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
#include "DirectoryHierarchyManager.h" 
#include "AssessmentMetricsCalculator.h"

UBaseGameInstance::UBaseGameInstance()
{
    //DirectoryManager = NewObject<UDirectoryHierarchyManager>(this);
    DirectoryManager = CreateDefaultSubobject<UDirectoryHierarchyManager>(TEXT("DirectoryManager"));

}

void UBaseGameInstance::Init()
{
    Super::Init();

    UWorld* World = GetWorld();  // Assuming this is called within an actor or component

       

    // Create an instance of UDataProvider
    DataProvider = NewObject<UDataProvider>(this);

    // Call the ConstructHierarchy function
    DataProvider->ConstructHierarchy();

    // Store the DataProvider in a property if you need to access it later
    this->DataProvider = DataProvider;

    // Generate some resources
    TArray<FResourceStruct> resources;
    for (int i = 1; i <= 3; i++)
    {
        FResourceStruct resource;
        resource.Name = FString::Printf(TEXT("Resource%d"), i);
        resources.Add(resource);
    }

    // Generate some subjects, each with the same set of resources
    TArray<FHierarchySubjectStruct> subjects;
    for (int i = 1; i <= 3; i++)
    {
        FHierarchySubjectStruct subject;
        subject.Name = FString::Printf(TEXT("Subject%d"), i);
        subject.Resources = resources;  // Each subject gets a copy of the list of resources
        subjects.Add(subject);
    }

    // Generate some areas, each with the same set of subjects
    TArray<FAreaStruct> areas;
    for (int i = 1; i <= 3; i++)
    {
        FAreaStruct area;
        area.Name = FString::Printf(TEXT("Area%d"), i);
        area.Subjects = subjects;  // Each area gets a copy of the list of subjects
        areas.Add(area);
    }

    // Generate some fields, each with the same set of areas
    TArray<FFieldStruct> fields;
    for (int i = 1; i <= 3; i++)
    {
        FFieldStruct field;
        field.Name = FString::Printf(TEXT("Field%d"), i);
        field.Areas = areas;  // Each field gets a copy of the list of areas
        fields.Add(field);
    }
}


void UBaseGameInstance::InitializeSubjectDataArray()
{

}




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




