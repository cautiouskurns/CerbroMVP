// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportWidget.h"
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
