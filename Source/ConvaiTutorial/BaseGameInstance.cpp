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
#include "Misc/FileHelper.h"
#include "FolderWidget.h"

UBaseGameInstance::UBaseGameInstance()
{
 
}

void UBaseGameInstance::InitializeSubjectDataArray()
{
    //FFolderStruct Struct1;
    //Struct1.SubjectName = "Law";
    //SubjectDataArray.Add(Struct1);

    //FFolderStruct Struct2;
    //Struct2.SubjectName = "Physics";
    //SubjectDataArray.Add(Struct2);

    //FFolderStruct Struct3;
    //Struct3.SubjectName = "Chemistry";
    //SubjectDataArray.Add(Struct3);

    //FFolderStruct Struct4;
    //Struct4.SubjectName = "Biology";
    //SubjectDataArray.Add(Struct4);

    //FFolderStruct Struct5;
    //Struct5.SubjectName = "English";
    //SubjectDataArray.Add(Struct5);

    //FFolderStruct Struct6;
    //Struct6.SubjectName = "French";
    //SubjectDataArray.Add(Struct6);

    //FFolderStruct Struct7;
    //Struct7.SubjectName = "German";
    //SubjectDataArray.Add(Struct7);

    //FFolderStruct Struct8;
    //Struct8.SubjectName = "Spanish";
    //SubjectDataArray.Add(Struct8);

    //FFolderStruct Struct9;
    //Struct9.SubjectName = "Economics";
    //SubjectDataArray.Add(Struct9);

    //FFolderStruct Struct10;
    //Struct10.SubjectName = "History";
    //SubjectDataArray.Add(Struct10);

    //FFolderStruct Struct11;

    //Struct11.SubjectName = "Geography";
    //SubjectDataArray.Add(Struct11);

    //FFolderStruct Struct12;
    //Struct12.SubjectName = "Computer Science";
    //SubjectDataArray.Add(Struct12);

    //FFolderStruct Struct13;
    //Struct13.SubjectName = "Philosophy";
    //SubjectDataArray.Add(Struct13);

    //FFolderStruct Struct14;
    //Struct14.SubjectName = "Psychology";
    //SubjectDataArray.Add(Struct14);

    //FFolderStruct Struct15;
    //Struct15.SubjectName = "Political Science";
    //SubjectDataArray.Add(Struct15);

    //FFolderStruct Struct16;
    //Struct16.SubjectName = "Sociology";
    //SubjectDataArray.Add(Struct16);

    //FFolderStruct Struct17;
    //Struct17.SubjectName = "Astronomy";
    //SubjectDataArray.Add(Struct17);

    //FFolderStruct Struct18;
    //Struct18.SubjectName = "Music";
    //SubjectDataArray.Add(Struct18);

    //FFolderStruct Struct19;
    //Struct19.SubjectName = "Art";
    //SubjectDataArray.Add(Struct19);

    //FFolderStruct Struct20;
    //Struct20.SubjectName = "Theatre";
    //SubjectDataArray.Add(Struct20);
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


//FSubjectStruct UReadWriteJsonFile::ReadNestedStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
//{
//    JsonFilePath = FPaths::ProjectContentDir() + "JSONStructTest1.json";
//    bOutSuccess = true;
//
//
//    // Reads a JSON file and attempts to deserialize it into a FJsonStruct object.
//    TSharedPtr<FJsonObject> JsonObject = ReadJsonFileToJsonObject(JsonFilePath, bOutSuccess, OutInfoMessage);
//    if (!bOutSuccess)
//    {
//        OutInfoMessage = FString::Printf(TEXT("JSON file not read successfully"));
//
//        // Deserialize the JSON data into a FJsonStruct object.
//        return FSubjectStruct();
//    }
//
//    // Convert a JsonObject into a FJsonStruct instance.
//    // If we failed to serialize the JSON data, then we return an empty FJsonStruct object.
//    FSubjectStruct StructToReturn;
//    if (!FJsonObjectConverter::JsonObjectToUStruct<FSubjectStruct>(JsonObject.ToSharedRef(), &StructToReturn, 0, 0))
//    {
//        bOutSuccess = false;
//        OutInfoMessage = FString::Printf(TEXT("Failed to convert JSON object to struct"));
//        return FSubjectStruct();
//    }
//
//
//    bOutSuccess = true;
//    OutInfoMessage = FString::Printf(TEXT("Convert JSON object to struct"));
//    return StructToReturn;
//}



//void UBaseGameInstance::PopulateTreeView(UTreeView* TreeView)
//{
//    TMap<int32, UFolderWidget*> WidgetMap;
//
//    for (FTreeViewItem& Item : TreeDataArray)
//    {
//        USubjectWidget* NewWidget = CreateWidget<USubjectWidget>(this, USubjectWidget::StaticClass());
//        NewWidget->SetData(Item);
//        TreeView->AddItem(NewWidget);
//    }
//
//    // Add the root items to the TreeView and the rest to their parents.
//    for (FTreeViewItem& Item : TreeDataArray)
//    {
//        UFolderWidget* ThisWidget = WidgetMap.FindRef(Item.ID);
//        if (Item.ParentID == -1)  // This is a root item
//        {
//            TreeView->AddItem(ThisWidget);
//        }
//        else  // This is a child item
//        {
//            UFolderWidget* ParentWidget = WidgetMap.FindRef(Item.ParentID);
//            if (ParentWidget)
//            {
//                ParentWidget->AddChild(ThisWidget);
//            }
//        }
//    }
//}
//
//
//TArray<FListViewItem> UBaseGameInstance::GetListData()
//{
//    TArray<FListViewItem> ListData;
//
//    // Populate ListData with your data here...
//
//    return ListData;
//}

