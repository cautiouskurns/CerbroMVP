// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"
#include "ConvaiTutorial/DataManagement/DataProvider.h"
#include "ConvaiTutorial/DataManagement/FieldDataManager.h"
#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"
#include "ConvaiTutorial/ContentRecommendationManagement/ContentRecommendationManager.h"
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

#include <fstream>
#include <sstream>

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

    // Construct UAssessmentMetricsCalculator and pass in UserInteractionDataManager
    AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>(this);
    AssessmentMetricsCalculator->SetUserInteractionDataManager(UserInteractionDataManager);

    ContentRecommendationManager = NewObject<UContentRecommendationManager>(this);


    // Create an instance of UDataProvider
    DataProvider = NewObject<UDataProvider>(this);

    // Call the ConstructHierarchy function
    DataProvider->ConstructHierarchy();

    // Store the DataProvider in a property if you need to access it later
    this->DataProvider = DataProvider;
}


void UBaseGameInstance::InitializeDataManagers()
{
    // Construct FieldDataManager and UserInteractionDataManager
    FieldDataManager = NewObject<UFieldDataManager>(this);
    UserInteractionDataManager = NewObject<UUserInteractionDataManager>(this);

    // Initialize UserInteractions
    UserInteractionDataManager->InitializeUserInteractions(FieldDataArray);

    // Register the observer
    FieldDataManager->RegisterObserver(UserInteractionDataManager);

    // Initialize ContentRecommendationManager
    ContentRecommendationManager = NewObject<UContentRecommendationManager>(this);
    ContentRecommendationManager->InitializeDataManagers(UserInteractionDataManager);


    UE_LOG(LogTemp, Warning, TEXT("FieldDataManager: %s"), *FieldDataManager->ToString());
    UE_LOG(LogTemp, Warning, TEXT("UserInteractionDataManager: %s"), *UserInteractionDataManager->ToString());

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

    if (SaveGameObject == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("SaveGameObject is null in SaveGameData"));
        return;
    }

    if (UserInteractionDataManager == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("UserInteractionDataManager is null in SaveGameData"));
        return;
    }

    SaveGameObject->UserInteractionsSaveData = UserInteractionDataManager->GetUserInteractions(); // assuming you have such a getter method in your UserInteractionDataManager


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

        UserInteractionDataManager->SetUserInteractions(SaveGameObject->UserInteractionsSaveData); // assuming you have such a setter method in your UserInteractionDataManager

    }
}


int32 UBaseGameInstance::UpdateRandomQuestionTimesTested(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex)
{
    return AssessmentMetricsCalculator->UpdateRandomQuestionTimesTested(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionIndex, SubjectDataArray);
}

int32 UBaseGameInstance::UpdateTimesCorrect(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer)
{
    return AssessmentMetricsCalculator->UpdateTimesCorrect(SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionIndex, SelectedAnswer, SubjectDataArray);
}

int32 UBaseGameInstance::CalculateTimesAskedForSubtopicIR(const FString& SubtopicTitle)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForSubtopicIR(SubtopicTitle, FieldDataArray);
}

int32 UBaseGameInstance::CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle)
{
	return AssessmentMetricsCalculator->CalculateTimesCorrectForSubtopicIR(SubtopicTitle, FieldDataArray);
}

FTest UBaseGameInstance::UpdateTimesTestedAndCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, const FString& SelectedAnswer)
{
    return AssessmentMetricsCalculator->UpdateTimesTestedAndCorrectForQuestion( SubjectIndex,  SectionIndex,  TopicIndex,  SubtopicIndex,  QuestionText,  SelectedAnswer, SubjectDataArray);
}

FString UBaseGameInstance::SubmitAnswer(const FString& AnswerText)
{
    AssessmentMetricsCalculator->SubmitAnswer(AnswerText);

    return AnswerText;
}

FTest UBaseGameInstance::UpdateAnswerStatus(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    return AssessmentMetricsCalculator->UpdateAnswerStatus(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, FieldDataArray);
}


int32 UBaseGameInstance::GetTimesTestedForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    return AssessmentMetricsCalculator->GetTimesTestedForQuestion(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, FieldDataArray);
}


// New function to get the number of times a specific question has been answered correctly
int32 UBaseGameInstance::GetTimesCorrectForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText)
{
    return AssessmentMetricsCalculator->GetTimesCorrectForQuestion(FieldIndex, AreaIndex, SubjectGroupIndex, SubjectIndex, SectionIndex, TopicIndex, SubtopicIndex, QuestionText, FieldDataArray); 
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



void UBaseGameInstance::LoadDataFromCSV(const FString& FilePath)
{
    std::ifstream file(TCHAR_TO_UTF8(*FilePath));

    std::string line;
    // Skip headers
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;

        FFieldStruct field;
        FAreaStruct area;
        FSubjectGroupStruct subjectGroup;
        FSubjectStruct subject;
        FSectionStruct section;
        FTopic topic;
        FSubtopic subtopic;
        FTest question;

        if (std::getline(iss, token, ','))
        {
            field.FieldName = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            area.AreaName = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            subjectGroup.SubjectGroupName = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            subject.SubjectName = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            section.SectionName = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            topic.Title = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            subtopic.Title = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            subtopic.Content = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            question.Question = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            // Assuming answers are stored as a semicolon-separated string
            TArray<FString> answers;
            FString(token.c_str()).ParseIntoArray(answers, TEXT(";"));
            question.Answers = answers;
        }

        if (std::getline(iss, token, ','))
        {
            question.CorrectAnswer = FString(token.c_str());
        }

        if (std::getline(iss, token, ','))
        {
            question.TimesTested = FCString::Atoi(*FString(token.c_str()));
        }

        if (std::getline(iss, token, ','))
        {
            question.TimesCorrect = FCString::Atoi(*FString(token.c_str()));
        }

        if (std::getline(iss, token, ','))
        {
            question.ProficiencyScore = FCString::Atof(*FString(token.c_str()));
        }

        // Construct your data structure here
        topic.Subtopics.Add(subtopic);
        section.Topics.Add(topic);
        subject.SubjectDetailsArray.Add(section);
        subjectGroup.Subjects.Add(subject);
        area.SubjectGroups.Add(subjectGroup);
        field.Areas.Add(area);
        FieldDataArray.Add(field);
    }
}




const FFieldInteractionData* UBaseGameInstance::GetFieldInteractionData(const FString& FieldName)
{
    return UserInteractionDataManager->GetFieldInteractionData(FieldName);
}

const FAreaInteractionData* UBaseGameInstance::GetAreaInteractionData(const FString& AreaName, const FFieldInteractionData& FieldData)
{
    return UserInteractionDataManager->GetAreaInteractionData(AreaName, FieldData);
}

const FSubjectGroupInteractionData* UBaseGameInstance::GetSubjectGroupInteractionData(const FString& SubjectGroupName, const FAreaInteractionData& AreaData)
{
	return UserInteractionDataManager->GetSubjectGroupInteractionData(SubjectGroupName, AreaData);
}

const FSubjectInteractionData* UBaseGameInstance::GetSubjectInteractionData(const FString& SubjectName, const FSubjectGroupInteractionData& SubjectGroupData)
{
	return UserInteractionDataManager->GetSubjectInteractionData(SubjectName, SubjectGroupData);
}

const FSectionInteractionData* UBaseGameInstance::GetSectionInteractionData(const FString& SectionName, const FSubjectInteractionData& LocalSubjectData)
{
	return UserInteractionDataManager->GetSectionInteractionData(SectionName, LocalSubjectData);
}

const FTopicInteractionData* UBaseGameInstance::GetTopicInteractionData(const FString& TopicName, const FSectionInteractionData& SectionData)
{
	return UserInteractionDataManager->GetTopicInteractionData(TopicName, SectionData);
}

const FSubtopicInteractionData* UBaseGameInstance::GetSubtopicInteractionData(const FString& SubtopicName, const FTopicInteractionData& TopicData)
{
	return UserInteractionDataManager->GetSubtopicInteractionData(SubtopicName, TopicData);
}




const FSubtopicInteractionData* UBaseGameInstance::FindSubtopicInteractionDataByName(const FString& SubtopicName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (const auto& TopicPair : SectionPair.Value.Topics)
                        {
                            for (auto& SubtopicPair : TopicPair.Value.Subtopics)
                            {
                                if (SubtopicPair.Key == SubtopicName)
                                {
                                    return &SubtopicPair.Value;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return nullptr; // Return nullptr if no subtopic with the given name is found
}

const FTopicInteractionData* UBaseGameInstance::FindTopicInteractionDataByName(const FString& TopicName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (auto& TopicPair : SectionPair.Value.Topics)
                        {
                            if (TopicPair.Key == TopicName)
                            {
                                return &TopicPair.Value;
                            }
                        }
                    }
                }
            }
        }
    }

    return nullptr; // Return nullptr if no topic with the given name is found
}






//float UBaseGameInstance::CalculateProficiencyForSubtopic(const FString& SubtopicName)
//{
//    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();
//
//    for (const auto& FieldPair : UserInteractions.Fields)
//    {
//        for (const auto& AreaPair : FieldPair.Value.Areas)
//        {
//            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
//            {
//                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
//                {
//                    for (const auto& SectionPair : SubjectPair.Value.Sections)
//                    {
//                        for (const auto& TopicPair : SectionPair.Value.Topics)
//                        {
//                            for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
//                            {
//                                if (SubtopicPair.Key == SubtopicName)
//                                {
//                                    return ContentRecommendationManager->CalculateProficiencyForSubtopic(SubtopicPair.Value);
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return 0.0f; // Return 0.0 if no subtopic with the given name is found
//}

float UBaseGameInstance::CalculateProficiencyForSubtopic(const FString& SubtopicName)
{
    const FSubtopicInteractionData* SubtopicData = FindSubtopicInteractionDataByName(SubtopicName);
    if (!SubtopicData)
    {
        return 0.0f; // Return 0.0f if no subtopic with the given name is found
    }

    return ContentRecommendationManager->CalculateProficiencyForSubtopic(*SubtopicData);
}

float UBaseGameInstance::CalculateProficiencyForTopic(const FString& TopicName)
{
    const FTopicInteractionData* TopicData = FindTopicInteractionDataByName(TopicName);
    if (!TopicData)
    {
        return 0.0f; // Return 0.0f if no topic with the given name is found
    }

    return ContentRecommendationManager->CalculateProficiencyForTopic(*TopicData);
}



//float UBaseGameInstance::CalculateProficiencyForTopic(const FString& TopicName)
//{
//    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();
//
//    for (const auto& FieldPair : UserInteractions.Fields)
//    {
//        for (const auto& AreaPair : FieldPair.Value.Areas)
//        {
//            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
//            {
//                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
//                {
//                    for (const auto& SectionPair : SubjectPair.Value.Sections)
//                    {
//                        for (const auto& TopicPair : SectionPair.Value.Topics)
//                        {
//                            if (TopicPair.Key == TopicName)
//                            {
//                                return ContentRecommendationManager->CalculateProficiencyForTopic(TopicPair.Value);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return 0.0f; // Return 0.0 if no topic with the given name is found
//}


float UBaseGameInstance::CalculateProficiencyForSection(const FString& SectionName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        if (SectionPair.Key == SectionName)
                        {
                            return ContentRecommendationManager->CalculateProficiencyForSection(SectionPair.Value);
                        }
                    }
                }
            }
        }
    }

    return 0.0f; // Return 0.0 if no section with the given name is found
}

float UBaseGameInstance::CalculateProficiencyForSubject(const FString& SubjectName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    if (SubjectPair.Key == SubjectName)
                    {
                        return ContentRecommendationManager->CalculateProficiencyForSubject(SubjectPair.Value);
                    }
                }
            }
        }
    }

    return 0.0f; // Return 0.0 if no subject with the given name is found
}


float UBaseGameInstance::CalculateProficiencyForSubjectGroup(const FString& SubjectGroupName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                if (SubjectGroupPair.Key == SubjectGroupName)
                {
                    return ContentRecommendationManager->CalculateProficiencyForSubjectGroup(SubjectGroupPair.Value);
                }
            }
        }
    }

    return 0.0f; // Return 0.0 if no subject group with the given name is found
}

float UBaseGameInstance::CalculateProficiencyForArea(const FString& AreaName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            if (AreaPair.Key == AreaName)
            {
                return ContentRecommendationManager->CalculateProficiencyForArea(AreaPair.Value);
            }
        }
    }

    return 0.0f; // Return 0.0 if no area with the given name is found
}

float UBaseGameInstance::CalculateProficiencyForField(const FString& FieldName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        if (FieldPair.Key == FieldName)
        {
            return ContentRecommendationManager->CalculateProficiencyForField(FieldPair.Value);
        }
    }

    return 0.0f; // Return 0.0 if no field with the given name is found
}






float UBaseGameInstance::CalculateSubtopicRecommendationScore(const FString& SubtopicName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (const auto& TopicPair : SectionPair.Value.Topics)
                        {
                            for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                            {
                                if (SubtopicPair.Key == SubtopicName)
                                {
                                    return ContentRecommendationManager->CalculateSubtopicRecommendationScore(SubtopicPair.Value);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0.0f; // Return 0.0 if no subtopic with the given name is found
}

float UBaseGameInstance::CalculateTopicRecommendationScore(const FString& TopicName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (const auto& TopicPair : SectionPair.Value.Topics)
                        {
                            if (TopicPair.Key == TopicName)
                            {
                                return ContentRecommendationManager->CalculateTopicRecommendationScore(TopicPair.Value);
                            }
                        }
                    }
                }
            }
        }
    }

    return 0.0f; // Return 0.0 if no topic with the given name is found
}


float UBaseGameInstance::CalculateSectionRecommendationScore(const FString& SectionName)
{
    const FUserInteractionData& UserInteractions = UserInteractionDataManager->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        if (SectionPair.Key == SectionName)
                        {
                            return ContentRecommendationManager->CalculateSectionRecommendationScore(SectionPair.Value);
                        }
                    }
                }
            }
        }
    }

    return 0.0f; // Return 0.0 if no section with the given name is found
}








int32 UBaseGameInstance::CalculateTimesAskedForSubtopic(const FString& SubtopicName, const FTopicInteractionData& TopicData)
{
    return UserInteractionDataManager->CalculateTimesAskedForSubtopic(SubtopicName, TopicData);
}


int32 UBaseGameInstance::CalculateTimesAskedForSubtopicInteract(const FString& SubtopicName)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForSubtopicInteract(SubtopicName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesAskedForTopicInteract(const FString& TopicName)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForTopicInteract(TopicName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesAskedForSectionInteract(const FString& SectionName)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForSectionInteract(SectionName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesAskedForSubjectInteract(const FString& SubjectName)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForSubjectInteract(SubjectName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesAskedForSubjectGroupInteract(const FString& SubjectGroupName)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForSubjectGroupInteract(SubjectGroupName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesAskedForAreaInteract(const FString& AreaName)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForAreaInteract(AreaName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesAskedForFieldInteract(const FString& FieldName)
{
    return AssessmentMetricsCalculator->CalculateTimesAskedForFieldInteract(FieldName, UserInteractionDataManager);
}



int32 UBaseGameInstance::CalculateTimesCorrectForSubtopicInteract(const FString& SubtopicName)
{
    return AssessmentMetricsCalculator->CalculateTimesCorrectForSubtopicInteract(SubtopicName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesCorrectForTopicInteract(const FString& TopicName)
{
    return AssessmentMetricsCalculator->CalculateTimesCorrectForTopicInteract(TopicName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesCorrectForSectionInteract(const FString& SectionName)
{
    return AssessmentMetricsCalculator->CalculateTimesCorrectForSectionInteract(SectionName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesCorrectForSubjectInteract(const FString& SubjectName)
{
    return AssessmentMetricsCalculator->CalculateTimesCorrectForSubjectInteract(SubjectName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesCorrectForSubjectGroupInteract(const FString& SubjectGroupName)
{
    return AssessmentMetricsCalculator->CalculateTimesCorrectForSubjectGroupInteract(SubjectGroupName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesCorrectForAreaInteract(const FString& AreaName)
{
    return AssessmentMetricsCalculator->CalculateTimesCorrectForAreaInteract(AreaName, UserInteractionDataManager);
}

int32 UBaseGameInstance::CalculateTimesCorrectForFieldInteract(const FString& FieldName)
{
    return AssessmentMetricsCalculator->CalculateTimesCorrectForFieldInteract(FieldName, UserInteractionDataManager);
}



void UBaseGameInstance::UpdateProficiencyForSubtopic(const FString& SubtopicName, float NewProficiencyScore)
{
    return UserInteractionDataManager->UpdateProficiencyForSubtopic(SubtopicName, NewProficiencyScore);
}
float UBaseGameInstance::GetProficiencyForSubtopic(const FString& SubtopicName)
{
    return UserInteractionDataManager->GetProficiencyForSubtopic(SubtopicName);
}

void UBaseGameInstance::UpdateProficiencyForTopic(const FString& TopicName, float NewProficiencyScore)
{
    return UserInteractionDataManager->UpdateProficiencyForTopic(TopicName, NewProficiencyScore);
}
float UBaseGameInstance::GetProficiencyForTopic(const FString& TopicName)
{
    return UserInteractionDataManager->GetProficiencyForTopic(TopicName);
}

void UBaseGameInstance::UpdateProficiencyForSection(const FString& SectionName, float NewProficiencyScore)
{
	return UserInteractionDataManager->UpdateProficiencyForSection(SectionName, NewProficiencyScore);
}
float UBaseGameInstance::GetProficiencyForSection(const FString& SectionName)
{
    return UserInteractionDataManager->GetProficiencyForSection(SectionName);
}