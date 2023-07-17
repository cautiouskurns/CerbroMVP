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
#include "MySaveGame.h"
#include <Kismet/GameplayStatics.h>

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
}


void UBaseGameInstance::InitializeSubjectDataArray()
{

}


void UBaseGameInstance::PopulateFieldDataArrayFromDataTable(UDataTable* DataTable)
{
    // Load the data table
    //UDataTable* DataTable = LoadObject<UDataTable>(NULL, TEXT("/Game/YourPath/YourDataTable.YourDataTable"));
    if (DataTable == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Data table not found!"));
        return;
    }

    // Get all row names
    TArray<FName> RowNames = DataTable->GetRowNames();

    // Iterate over each row
    for (const FName& RowName : RowNames)
    {
        static const FString ContextString(TEXT("GENERAL"));
        FFieldStruct* Row = DataTable->FindRow<FFieldStruct>(RowName, ContextString);
        if (Row == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Row not found!"));
            continue;
        }

        // Add the row data to FieldDataArray
        FieldDataArray.Add(*Row);
    }
}


//void UBaseGameInstance::SaveGameData()
//{
//    UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
//
//    for (const FFieldStruct& FieldData : FieldDataArray)
//    {
//        FFieldStructSaveData FieldDataSave;
//        FieldDataSave.FieldName = FieldData.FieldName;
//        for (const FAreaStruct& AreaData : FieldData.Areas)
//        {
//            FAreaStructSaveData AreaDataSave;
//            AreaDataSave.AreaName = AreaData.AreaName;
//            for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
//            {
//                FSubjectGroupStructSaveData SubjectGroupDataSave;
//                SubjectGroupDataSave.SubjectGroupName = SubjectGroupData.SubjectGroupName;
//                for (const FSubjectStruct& NewSubjectData : SubjectGroupData.Subjects)
//                {
//                    FSubjectStructSaveData SubjectDataSave;
//                    SubjectDataSave.SubjectName = NewSubjectData.SubjectName;
//
//                    SubjectGroupDataSave.SubjectsSaveData.Add(SubjectDataSave);
//                }
//                AreaDataSave.SubjectGroupsSaveData.Add(SubjectGroupDataSave);
//            }
//            FieldDataSave.AreasSaveData.Add(AreaDataSave);
//        }
//        SaveGameObject->FieldDataArraySaveData.Add(FieldDataSave);
//    }
//
//    UGameplayStatics::SaveGameToSlot(SaveGameObject, TEXT("YourSaveSlot"), 0);
//}

void UBaseGameInstance::SaveGameData()
{
    UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

    for (const FFieldStruct& FieldData : FieldDataArray)
    {
        FFieldStructSaveData FieldDataSave;
        FieldDataSave.FieldName = FieldData.FieldName;

        for (const FAreaStruct& AreaData : FieldData.Areas)
        {
            FAreaStructSaveData AreaDataSave;
            AreaDataSave.AreaName = AreaData.AreaName;

            for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
            {
                FSubjectGroupStructSaveData SubjectGroupDataSave;
                SubjectGroupDataSave.SubjectGroupName = SubjectGroupData.SubjectGroupName;

                for (const FSubjectStruct& SubjectDataNew : SubjectGroupData.Subjects)
                {
                    FSubjectStructSaveData SubjectDataSave;
                    SubjectDataSave.SubjectName = SubjectDataNew.SubjectName;
                    SubjectDataSave.InputType = SubjectDataNew.InputType;
                    SubjectDataSave.InteractionMetadataArray = SubjectDataNew.InteractionMetadataArray;

                    for (const FSectionStruct& SectionData : SubjectDataNew.SubjectDetailsArray)
                    {
                        FSectionStructSaveData SectionDataSave;
                        SectionDataSave.SectionName = SectionData.SectionName;

                        for (const FTopic& TopicData : SectionData.Topics)
                        {
                            FTopicSaveData TopicDataSave;
                            TopicDataSave.Title = TopicData.Title;

                            for (const FSubtopic& SubtopicData : TopicData.Subtopics)
                            {
                                FSubtopicSaveData SubtopicDataSave;
                                SubtopicDataSave.Title = SubtopicData.Title;
                                SubtopicDataSave.Content = SubtopicData.Content;

                                for (const FTest& TestData : SubtopicData.Questions)
                                {
                                    FTestSaveData TestDataSave;
                                    TestDataSave.Question = TestData.Question;
                                    TestDataSave.CorrectAnswer = TestData.CorrectAnswer;
                                    TestDataSave.TimesTested = TestData.TimesTested;
                                    TestDataSave.TimesCorrect = TestData.TimesCorrect;
                                    TestDataSave.ProficiencyScore = TestData.ProficiencyScore;

                                    SubtopicDataSave.QuestionsSaveData.Add(TestDataSave);
                                }

                                TopicDataSave.SubtopicsSaveData.Add(SubtopicDataSave);
                            }

                            SectionDataSave.TopicsSaveData.Add(TopicDataSave);
                        }

                        SubjectDataSave.SubjectDetailsArraySaveData.Add(SectionDataSave);
                    }

                    SubjectGroupDataSave.SubjectsSaveData.Add(SubjectDataSave);
                }

                AreaDataSave.SubjectGroupsSaveData.Add(SubjectGroupDataSave);
            }

            FieldDataSave.AreasSaveData.Add(AreaDataSave);
        }

        SaveGameObject->FieldDataArraySaveData.Add(FieldDataSave);
    }

    UGameplayStatics::SaveGameToSlot(SaveGameObject, TEXT("YourSaveSlot"), 0);
}

//void UBaseGameInstance::LoadGameData()
//{
//    if (UGameplayStatics::DoesSaveGameExist(TEXT("YourSaveSlot"), 0))
//    {
//        UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("YourSaveSlot"), 0));
//
//        if (SaveGameObject)
//        {
//            FieldDataArray.Empty();
//            for (const FFieldStructSaveData& FieldDataSave : SaveGameObject->FieldDataArraySaveData)
//            {
//                FFieldStruct FieldData;
//                FieldData.FieldName = FieldDataSave.FieldName;
//                for (const FAreaStructSaveData& AreaDataSave : FieldDataSave.AreasSaveData)
//                {
//                    FAreaStruct AreaData;
//                    AreaData.AreaName = AreaDataSave.AreaName;
//                    for (const FSubjectGroupStructSaveData& SubjectGroupDataSave : AreaDataSave.SubjectGroupsSaveData)
//                    {
//                        FSubjectGroupStruct SubjectGroupData;
//                        SubjectGroupData.SubjectGroupName = SubjectGroupDataSave.SubjectGroupName;
//                        for (const FSubjectStructSaveData& SubjectDataSave : SubjectGroupDataSave.SubjectsSaveData)
//                        {
//                            FSubjectStruct NewSubjectData;
//                            NewSubjectData.SubjectName = SubjectDataSave.SubjectName;
//                            // ... copy other data ...
//                            SubjectGroupData.Subjects.Add(NewSubjectData);
//                        }
//                        AreaData.SubjectGroups.Add(SubjectGroupData);
//                    }
//                    FieldData.Areas.Add(AreaData);
//                }
//                FieldDataArray.Add(FieldData);
//            }
//        }
//    }
//}


void UBaseGameInstance::LoadGameData()
{
    if (UGameplayStatics::DoesSaveGameExist(TEXT("YourSaveSlot"), 0))
    {
        UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("YourSaveSlot"), 0));

        if (SaveGameObject)
        {
            // Clear existing data
            FieldDataArray.Empty();

            // Load all data from SaveGameObject->FieldDataArraySaveData to FieldDataArray
            for (const FFieldStructSaveData& FieldDataSave : SaveGameObject->FieldDataArraySaveData)
            {
                FFieldStruct FieldData;
                FieldData.FieldName = FieldDataSave.FieldName;

                for (const FAreaStructSaveData& AreaDataSave : FieldDataSave.AreasSaveData)
                {
                    FAreaStruct AreaData;
                    AreaData.AreaName = AreaDataSave.AreaName;

                    for (const FSubjectGroupStructSaveData& SubjectGroupDataSave : AreaDataSave.SubjectGroupsSaveData)
                    {
                        FSubjectGroupStruct SubjectGroupData;
                        SubjectGroupData.SubjectGroupName = SubjectGroupDataSave.SubjectGroupName;

                        for (const FSubjectStructSaveData& SubjectDataSave : SubjectGroupDataSave.SubjectsSaveData)
                        {
                            FSubjectStruct SubjectDataNew;
                            SubjectDataNew.SubjectName = SubjectDataSave.SubjectName;
                            SubjectDataNew.InputType = SubjectDataSave.InputType;
                            SubjectDataNew.InteractionMetadataArray = SubjectDataSave.InteractionMetadataArray;

                            for (const FSectionStructSaveData& SectionDataSave : SubjectDataSave.SubjectDetailsArraySaveData)
                            {
                                FSectionStruct SectionData;
                                SectionData.SectionName = SectionDataSave.SectionName;

                                for (const FTopicSaveData& TopicDataSave : SectionDataSave.TopicsSaveData)
                                {
                                    FTopic TopicData;
                                    TopicData.Title = TopicDataSave.Title;

                                    for (const FSubtopicSaveData& SubtopicDataSave : TopicDataSave.SubtopicsSaveData)
                                    {
                                        FSubtopic SubtopicData;
                                        SubtopicData.Title = SubtopicDataSave.Title;
                                        SubtopicData.Content = SubtopicDataSave.Content;

                                        // Convert each FTestSaveData to FTest
                                        for (const FTestSaveData& TestSaveData : SubtopicDataSave.QuestionsSaveData)
                                        {
                                            FTest Test;
                                            Test.Question = TestSaveData.Question;
                                            Test.Answers = TestSaveData.Answers;
                                            Test.CorrectAnswer = TestSaveData.CorrectAnswer;
                                            Test.TimesTested = TestSaveData.TimesTested;
                                            Test.TimesCorrect = TestSaveData.TimesCorrect;
                                            Test.ProficiencyScore = TestSaveData.ProficiencyScore;

                                            // Add the converted FTest to SubtopicData.Questions
                                            SubtopicData.Questions.Add(Test);
                                        }

                                        TopicData.Subtopics.Add(SubtopicData);
                                    }

                                    SectionData.Topics.Add(TopicData);
                                }

                                SubjectData.SubjectDetailsArray.Add(SectionData);
                            }

                            SubjectGroupData.Subjects.Add(SubjectData);
                        }

                        AreaData.SubjectGroups.Add(SubjectGroupData);
                    }

                    FieldData.Areas.Add(AreaData);
                }

                FieldDataArray.Add(FieldData);
            }
        }
    }
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




