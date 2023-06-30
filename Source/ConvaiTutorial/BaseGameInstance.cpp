// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "ReadWriteJsonFile.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "FolderWidget.h"
#include "ListViewItemBase.h"

UBaseGameInstance::UBaseGameInstance()
{
    FTreeViewItem RootItem;
    RootItem.ID = 0;
    RootItem.ParentID = -1;
    RootItem.Name = "Root";
    RootItem.ChildrenIDs = {}; // or some suitable value if you have child IDs to set

    FTreeViewItem ChildItem1;
    ChildItem1.ID = 1;
    ChildItem1.ParentID = 0;
    ChildItem1.Name = "Child 1";
    ChildItem1.ChildrenIDs = {}; // or some suitable value if you have child IDs to set

    FTreeViewItem ChildItem2;
    ChildItem2.ID = 2;
    ChildItem2.ParentID = 0;
    ChildItem2.Name = "Child 2";
    ChildItem2.ChildrenIDs = {}; // or some suitable value if you have child IDs to set


    FTreeViewItem ChildItem3;
    ChildItem3.ID = 3;
    ChildItem3.ParentID = 0;
    ChildItem3.Name = "Child 3";
    ChildItem3.ChildrenIDs = {}; // or some suitable value if you have child IDs to set


    // Add the test data to the array.
    TreeDataArray.Add(RootItem);
    TreeDataArray.Add(ChildItem1);
    TreeDataArray.Add(ChildItem2);
    TreeDataArray.Add(ChildItem3);
}


int32 UBaseGameInstance::UpdateRandomQuestionTimesTested(int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex)
{
    if (SectionDataArray.Num() > 0) // Check if there are any sections
    {
        //int32 SectionIndex = FMath::RandRange(0, SectionDataArray.Num() - 1); // Randomly select a section
        FSectionStruct& SelectedSection = SectionDataArray[SectionIndex];

        if (SelectedSection.Topics.Num() > 0) // Check if there are any topics in the selected section
        {
            //int32 TopicIndex = FMath::RandRange(0, SelectedSection.Topics.Num() - 1); // Randomly select a topic
            FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];

            if (SelectedTopic.Subtopics.Num() > 0) // Check if there are any subtopics in the selected topic
            {
                //int32 SubtopicIndex = FMath::RandRange(0, SelectedTopic.Subtopics.Num() - 1); // Randomly select a subtopic
                FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];

                if (SelectedSubtopic.Questions.Num() > 0) // Check if there are any questions in the selected subtopic
                {
                    //int32 QuestionIndex = FMath::RandRange(0, SelectedSubtopic.Questions.Num() - 1); // Randomly select a question
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



int32 UBaseGameInstance::UpdateTimesCorrect(int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer)
{
    if (SectionDataArray.IsValidIndex(SectionIndex)) // Check if the section index is valid
    {
        FSectionStruct& SelectedSection = SectionDataArray[SectionIndex];

        if (SelectedSection.Topics.IsValidIndex(TopicIndex)) // Check if the topic index is valid
        {
            FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];

            if (SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) // Check if the subtopic index is valid
            {
                FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];

                if (SelectedSubtopic.Questions.IsValidIndex(QuestionIndex)) // Check if the question index is valid
                {
                    FTest& SelectedQuestion = SelectedSubtopic.Questions[QuestionIndex];

                    // print selected answer to screen
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, SelectedAnswer);
                    //print correct answer to screen
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, SelectedQuestion.CorrectAnswer);

                    // If the selected answer matches the correct answer, increment the TimesCorrect member
                    if (SelectedAnswer == SelectedQuestion.CorrectAnswer)
                    {
                        // print that answers are the same to screen
                        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Answers are the same");
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

