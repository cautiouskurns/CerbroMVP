// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"
#include "ConvaiTutorial/DataManagement/DataProvider.h"
#include "ConvaiTutorial/DataManagement/MySaveGame.h"

#include "ConvaiTutorial/MetricHandling/AssessmentMetricsCalculator.h"

#include "ConvaiTutorial/Widgets/DirectoryHierarchyManager.h"
#include "ConvaiTutorial/Widgets/FolderWidget.h"

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
                                    TestDataSave.Answers = TestData.Answers;
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

                                SubjectDataNew.SubjectDetailsArray.Add(SectionData);
                            }

                            SubjectGroupData.Subjects.Add(SubjectDataNew);
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
    return AssessmentMetricsCalculator->CalculateTimesAskedForSubtopicIR(SubtopicTitle, FieldDataArray);
}

//int32 UBaseGameInstance::CalculateTimesAskedForQuestionIR(const FString& QuestionText)
//{
//    UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
//    return AssessmentMetricsCalculator->CalculateTimesAskedForQuestionIR(QuestionText, SubjectDataArray);
//}

int32 UBaseGameInstance::CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle)
{
	UAssessmentMetricsCalculator* AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>();
	return AssessmentMetricsCalculator->CalculateTimesCorrectForSubtopicIR(SubtopicTitle, FieldDataArray);
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

FTest UBaseGameInstance::UpdateAnswerStatus(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    if (AssessmentMetricsCalculatorGlobal == nullptr)
    {
        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
    }
    return AssessmentMetricsCalculatorGlobal->UpdateAnswerStatus(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, FieldDataArray);
}



//FTest UBaseGameInstance::UpdateAnswerStatus(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
//{
//    if (AssessmentMetricsCalculatorGlobal == nullptr)
//    {
//        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
//    }
//    return AssessmentMetricsCalculatorGlobal->UpdateAnswerStatus(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, SubjectDataArray);
//
//}


int32 UBaseGameInstance::GetTimesTestedForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    if (AssessmentMetricsCalculatorGlobal == nullptr)
    {
        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
    }
    return AssessmentMetricsCalculatorGlobal->GetTimesTestedForQuestion(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, FieldDataArray);
}



// New function to get the number of times a specific question has been answered correctly
int32 UBaseGameInstance::GetTimesCorrectForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    if (AssessmentMetricsCalculatorGlobal == nullptr)
    {
        AssessmentMetricsCalculatorGlobal = NewObject<UAssessmentMetricsCalculator>();
    }
    return AssessmentMetricsCalculatorGlobal->GetTimesCorrectForQuestion(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, FieldDataArray);
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



void UBaseGameInstance::LoadJsonArrayFromFile(FString FilePath, EStructLevelJSON StructLevel, const FString& ParentName)
{
    FString JsonContent;
    if (!FFileHelper::LoadFileToString(JsonContent, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
        return;
    }

    TArray<TSharedPtr<FJsonValue>> JsonArray;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);

    if (!FJsonSerializer::Deserialize(Reader, JsonArray) || JsonArray.Num() <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse the JSON in file: %s"), *FilePath);
        return;
    }

    switch (StructLevel)
    {
        case EStructLevelJSON::EL_Area:
        {
            TArray<FAreaStruct> LoadedStructs;
            if (FJsonObjectConverter::JsonArrayStringToUStruct(JsonContent, &LoadedStructs, 0, 0))
            {
                FFieldStruct* ParentField = FindFieldByName(ParentName);
                if (ParentField)
                {
                    ParentField->Areas.Append(LoadedStructs);
                }
            }
            break;
        }
        case EStructLevelJSON::EL_SubjectGroup:
        {
            TArray<FSubjectGroupStruct> LoadedStructs;
            if (FJsonObjectConverter::JsonArrayStringToUStruct(JsonContent, &LoadedStructs, 0, 0))
            {
                FAreaStruct* ParentArea = FindAreaByName(ParentName);
                if (ParentArea)
                {
                    ParentArea->SubjectGroups.Append(LoadedStructs);
                }
            }
            break;
        }
        case EStructLevelJSON::EL_Subject:
        {
            TArray<FSubjectStruct> LoadedStructs;
            if (FJsonObjectConverter::JsonArrayStringToUStruct(JsonContent, &LoadedStructs, 0, 0))
            {
                FSubjectGroupStruct* ParentSubjectGroup = FindSubjectGroupByName(ParentName);
                if (ParentSubjectGroup)
                {
                    ParentSubjectGroup->Subjects.Append(LoadedStructs);
                }
            }
            break;
        }
        case EStructLevelJSON::EL_Section:
        {
            TArray<FSectionStruct> LoadedStructs;
            if (FJsonObjectConverter::JsonArrayStringToUStruct(JsonContent, &LoadedStructs, 0, 0))
            {
                FSubjectStruct* ParentSubject = FindSubjectByName(ParentName);
                if (ParentSubject)
                {
                    ParentSubject->SubjectDetailsArray.Append(LoadedStructs);
                }
            }
            break;
        }
        case EStructLevelJSON::EL_Topic:
        {
            TArray<FTopic> LoadedStructs;
            if (FJsonObjectConverter::JsonArrayStringToUStruct(JsonContent, &LoadedStructs, 0, 0))
            {
                FSectionStruct* ParentSection = FindSectionByName(ParentName);
                if (ParentSection)
                {
                    ParentSection->Topics.Append(LoadedStructs);
                }
            }
            break;
        }
        case EStructLevelJSON::EL_Subtopic:
        {
            TArray<FSubtopic> LoadedStructs;
            if (FJsonObjectConverter::JsonArrayStringToUStruct(JsonContent, &LoadedStructs, 0, 0))
            {
                FTopic* ParentSection = FindTopicByName(ParentName);
                if (ParentSection)
                {
                    ParentSection->Subtopics.Append(LoadedStructs);
                }
            }
            break;
        }
    }
}



FFieldStruct* UBaseGameInstance::FindFieldByName(const FString& FieldName)
{
    for (auto& Field : FieldDataArray)
    {
        if (Field.FieldName == FieldName)
        {
            return &Field;
        }
    }

    return nullptr;
}

FAreaStruct* UBaseGameInstance::FindAreaByName(const FString& AreaName)
{
    for (auto& Field : FieldDataArray)
    {
        for (auto& Area : Field.Areas)
        {
            if (Area.AreaName == AreaName)
            {
                return &Area;
            }
        }
    }

    return nullptr;
}

FSubjectGroupStruct* UBaseGameInstance::FindSubjectGroupByName(const FString& SubjectGroupName)
{
    for (auto& Field : FieldDataArray)
    {
        for (auto& Area : Field.Areas)
        {
            for (auto& SubjectGroup : Area.SubjectGroups)
            {
                if (SubjectGroup.SubjectGroupName == SubjectGroupName)
                {
                    return &SubjectGroup;
                }
            }
        }
    }

    return nullptr;
}

FSubjectStruct* UBaseGameInstance::FindSubjectByName(const FString& SubjectName)
{
    for (auto& Field : FieldDataArray)
    {
        for (auto& Area : Field.Areas)
        {
            for (auto& SubjectGroup : Area.SubjectGroups)
            {
                for (auto& Subject : SubjectGroup.Subjects)
                {
                    if (Subject.SubjectName == SubjectName)
                    {
                        return &Subject;
                    }
                }
            }
        }
    }

    return nullptr;
}

FSectionStruct* UBaseGameInstance::FindSectionByName(const FString& SectionName)
{
    for (auto& Field : FieldDataArray)
    {
        for (auto& Area : Field.Areas)
        {
            for (auto& SubjectGroup : Area.SubjectGroups)
            {
                for (auto& Subject : SubjectGroup.Subjects)
                {
                    for (auto& Section : Subject.SubjectDetailsArray)
                    {
                        if (Section.SectionName == SectionName)
                        {
                            return &Section;
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}

FTopic* UBaseGameInstance::FindTopicByName(const FString& TopicName)
{
    for (auto& Field : FieldDataArray)
    {
        for (auto& Area : Field.Areas)
        {
            for (auto& SubjectGroup : Area.SubjectGroups)
            {
                for (auto& Subject : SubjectGroup.Subjects)
                {
                    for (auto& Section : Subject.SubjectDetailsArray)
                    {
                        for (auto& Topic : Section.Topics)
                        {
                            if (Topic.Title == TopicName)
                            {
                                return &Topic;
                            }
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}