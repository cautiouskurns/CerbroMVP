// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportWidget.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"


FString UImportWidget::OpenDialogForFile()
{
    // Set up the File Dialog properties
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    TArray<FString> OutFiles;
    FString DefaultPath = FPaths::ProjectDir();

    if (DesktopPlatform)
    {
        uint32 SelectionFlag = 0; // A value of 0 represents single file selection. Change this according to your requirement.

        DesktopPlatform->OpenFileDialog(
            nullptr,
            TEXT("Select a file"),
            DefaultPath,
            TEXT(""),
            TEXT("All Files (*.*)|*.*"),
            SelectionFlag,
            OutFiles
        );
    }

    if (OutFiles.Num() > 0)
    {
        SelectedFilePath = OutFiles[0]; // Assuming we're just interested in the first selected file
        // TODO: Set the text box text to SelectedFilePath and store it in a variable

        SelectedFilePath = FPaths::ConvertRelativePathToFull(SelectedFilePath);
        SelectedFilePath.ReplaceInline(TEXT("/"), TEXT("\\"));  // MyString now contains "Hello Universe!"

    }

    return SelectedFilePath;
}


FString UImportWidget::LoadJsonAsString(FString FilePath)
{
    FString JsonContent;
    if (!FFileHelper::LoadFileToString(JsonContent, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
        return TEXT(""); // Return an empty string on failure
    }

    // Return the JSON content as a string
    return JsonContent;
}


bool UImportWidget::UpdateSubjectName(const FString& SubjectName, const FString& NewSubjectName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return false;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            Subject.SubjectName = NewSubjectName;
            return true;
        }
    }

    return false; // Subject with given name not found
}




// Function to add a new section to an existing subject
void UImportWidget::AddSectionToSubject(FString SubjectName, FSectionStruct NewSection)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            // Add the new section to the subject details array
            Subject.SubjectDetailsArray.Add(NewSection);
            return;
        }
    }
}

bool UImportWidget::UpdateSectionName(const FString& SubjectName, const FString& SectionName, const FString& NewSectionName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return false;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            for (auto& Section : Subject.SubjectDetailsArray)
            {
                if (Section.SectionName == SectionName)
                {
                    Section.SectionName = NewSectionName;
                    return true;
                }
            }
        }
    }

    return false; // Subject or section with given name not found
}




void UImportWidget::AddTopicToSectionInSubject(FString SubjectName, FString SectionName, FTopic NewTopic)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            for (auto& Section : Subject.SubjectDetailsArray)
            {
                if (Section.SectionName == SectionName)
                {
                    // Here, instead of trying to find a matching topic and updating it,
                    // we just add the new topic to the topics array
                    Section.Topics.Add(NewTopic);
                    return;
                }
            }
        }
    }
}

bool UImportWidget::UpdateTopicName(const FString& SubjectName, const FString& SectionName, const FString& TopicName, const FString& NewTopicName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return false;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            for (auto& Section : Subject.SubjectDetailsArray)
            {
                if (Section.SectionName == SectionName)
                {
                    for (auto& Topic : Section.Topics)
                    {
                        if (Topic.Title == TopicName)
                        {
                            Topic.Title = NewTopicName;
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false; // Subject, section, or topic with given name not found
}




// Function to add a new subtopic to an existing topic
void UImportWidget::AddSubtopicToTopicInSection(FString SubjectName, FString SectionName, FString TopicName, FSubtopic NewSubtopic)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            for (auto& Section : Subject.SubjectDetailsArray)
            {
                if (Section.SectionName == SectionName)
                {
                    for (auto& Topic : Section.Topics)
                    {
                        if (Topic.Title == TopicName)
                        {
                            // Add the new subtopic to the subtopics array
                            Topic.Subtopics.Add(NewSubtopic);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UImportWidget::AddOrUpdateSubtopicInTopicInSection(FString SubjectName, FString SectionName, FString TopicName, FSubtopic NewSubtopic)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            for (auto& Section : Subject.SubjectDetailsArray)
            {
                if (Section.SectionName == SectionName)
                {
                    for (auto& Topic : Section.Topics)
                    {
                        if (Topic.Title == TopicName)
                        {
                            // Iterate over the Subtopics to see if one with the same title already exists
                            for (auto& Subtopic : Topic.Subtopics)
                            {
                                if (Subtopic.Title == NewSubtopic.Title)
                                {
                                    // Append the new content to the existing Subtopic
                                    Subtopic.Content += NewSubtopic.Content;
                                    return;
                                }
                            }

                            // If no existing Subtopic is found, add the new Subtopic
                            Topic.Subtopics.Add(NewSubtopic);
                            return;
                        }
                    }
                }
            }
        }
    }
}


bool UImportWidget::AddSubtopicToTopic(const FString& SubjectName, const FString& SectionName, const FString& TopicName, const FString& NewSubtopicName, const FString& NewSubtopicContent)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return false;

    for (auto& Subject : GameInstance->SubjectDataArray)
    {
        if (Subject.SubjectName == SubjectName)
        {
            for (auto& Section : Subject.SubjectDetailsArray)
            {
                if (Section.SectionName == SectionName)
                {
                    for (auto& Topic : Section.Topics)
                    {
                        if (Topic.Title == TopicName)
                        {
                            FSubtopic NewSubtopic;
                            NewSubtopic.Title = NewSubtopicName;
                            NewSubtopic.Content = NewSubtopicContent;

                            Topic.Subtopics.Add(NewSubtopic);
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false; // Subject, section, or topic with given name not found
}

