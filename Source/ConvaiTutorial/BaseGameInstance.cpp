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

UBaseGameInstance::UBaseGameInstance()
{
 
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
    //FFolderStruct Struct1;
    //Struct1.SubjectName = "Law";
    //SubjectDataArray.Add(Struct1);

    /*FString FilePath = FPaths::ProjectContentDir() + "StructTest.json";*/
}


int32 UBaseGameInstance::UpdateRandomQuestionTimesTested(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex)
{
    FSubjectStruct& SelectedSubject = SubjectDataArray[SubjectIndex];

    if (SelectedSubject.SubjectDetailsArray.Num() > 0) // Check if there are any sections
    {
        FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];

        if (SelectedSection.Topics.Num() > 0) // Check if there are any topics in the selected section
        {
            FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];

            if (SelectedTopic.Subtopics.Num() > 0) // Check if there are any subtopics in the selected topic
            {
                FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];

                if (SelectedSubtopic.Questions.Num() > 0) // Check if there are any questions in the selected subtopic
                {
                    FTest& SelectedQuestion = SelectedSubtopic.Questions[QuestionIndex];

                    // Increment the TimesTested property of the selected question
                    SelectedQuestion.TimesTested++;

                    // Return the updated TimesTested value
                    return SelectedQuestion.TimesTested;
                }
            }
        }
    }

    // Return -1 if any of the indices are invalid
    return -1;
}



int32 UBaseGameInstance::UpdateTimesCorrect(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer)
{
    FSubjectStruct& SelectedSubject = SubjectDataArray[SubjectIndex];

    if (SelectedSubject.SubjectDetailsArray.Num() > 0) // Check if there are any topics in the selected section
    {
        FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];

            if (SelectedSection.Topics.IsValidIndex(TopicIndex)) // Check if the topic index is valid
            {
                FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];

                if (SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) // Check if the subtopic index is valid
                {
                    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];

                    if (SelectedSubtopic.Questions.IsValidIndex(QuestionIndex)) // Check if the question index is valid
                    {
                        FTest& SelectedQuestion = SelectedSubtopic.Questions[QuestionIndex];

                        // If the selected answer matches the correct answer, increment the TimesCorrect member
                        if (SelectedAnswer == SelectedQuestion.CorrectAnswer)
                        {
                            // print that answers are the same to screen
                            SelectedQuestion.TimesCorrect++;
                            return SelectedQuestion.TimesCorrect;

                        }
                    }
                }
        }
    }
    // Return false if any of the indices are invalid or the answer is incorrect
    return 0;
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




