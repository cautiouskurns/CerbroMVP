// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportWidget.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"
#include "ConvaiTutorial/MyHttpClient.h"

#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include <Kismet/GameplayStatics.h>
#include <Components/ComboBoxString.h>


UImportWidget::UImportWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


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
















void UImportWidget::AddNewElement(EStructLevel Level, const FString& FieldName, const FString& AreaName, const FString& SubjectGroupName, 
    const FString& SubjectName, const FString& SectionName, const FString& TopicName, const FString& SubtopicName, 
    const FString& ElementName, const FString& ElementContent)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
    if (GameInstance == nullptr)
        return;

    switch (Level)
    {
    case EStructLevel::EL_Field:
    {
        FFieldStruct NewField;
        NewField.FieldName = ElementName;
        GameInstance->FieldDataArray.Add(NewField);
        break;
    }
    case EStructLevel::EL_Area:
    {
        for (auto& Field : GameInstance->FieldDataArray)
        {
            if (Field.FieldName == FieldName)
            {
                FAreaStruct NewArea;
                NewArea.AreaName = ElementName;
                Field.Areas.Add(NewArea);
                return;
            }
        }
        break;
    }
    case EStructLevel::EL_SubjectGroup:
    {
        for (auto& Field : GameInstance->FieldDataArray)
        {
            if (Field.FieldName == FieldName)
            {
                for (auto& Area : Field.Areas)
                {
                    if (Area.AreaName == AreaName)
                    {
                        FSubjectGroupStruct NewSubjectGroup;
                        NewSubjectGroup.SubjectGroupName = ElementName;
                        Area.SubjectGroups.Add(NewSubjectGroup);
                        return;
                    }
                }
            }
        }
        break;
    }
    case EStructLevel::EL_Subject:
    {
        for (auto& Field : GameInstance->FieldDataArray)
        {
            if (Field.FieldName == FieldName)
            {
                for (auto& Area : Field.Areas)
                {
                    if (Area.AreaName == AreaName)
                    {
                        for (auto& SubjectGroup : Area.SubjectGroups)
                        {
                            if (SubjectGroup.SubjectGroupName == SubjectGroupName)
                            {
                                FSubjectStruct NewSubject;
                                NewSubject.SubjectName = ElementName;
                                SubjectGroup.Subjects.Add(NewSubject);
                                return;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case EStructLevel::EL_Section:
    {
        for (auto& Field : GameInstance->FieldDataArray)
        {
            if (Field.FieldName == FieldName)
            {
                for (auto& Area : Field.Areas)
                {
                    if (Area.AreaName == AreaName)
                    {
                        for (auto& SubjectGroup : Area.SubjectGroups)
                        {
                            if (SubjectGroup.SubjectGroupName == SubjectGroupName)
                            {
                                for (auto& Subject : SubjectGroup.Subjects)
                                {
                                    if (Subject.SubjectName == SubjectName)
                                    {
                                        FSectionStruct NewSection;
                                        NewSection.SectionName = ElementName;
                                        Subject.SubjectDetailsArray.Add(NewSection);
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case EStructLevel::EL_Topic:
    {
        for (auto& Field : GameInstance->FieldDataArray)
        {
            if (Field.FieldName == FieldName)
            {
                for (auto& Area : Field.Areas)
                {
                    if (Area.AreaName == AreaName)
                    {
                        for (auto& SubjectGroup : Area.SubjectGroups)
                        {
                            if (SubjectGroup.SubjectGroupName == SubjectGroupName)
                            {
                                for (auto& Subject : SubjectGroup.Subjects)
                                {
                                    if (Subject.SubjectName == SubjectName)
                                    {
                                        for (auto& Section : Subject.SubjectDetailsArray)
                                        {
                                            if (Section.SectionName == SectionName)
                                            {
                                                FTopic NewTopic;
                                                NewTopic.Title = ElementName;
                                                Section.Topics.Add(NewTopic);
                                                return;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case EStructLevel::EL_Subtopic:
    {
        for (auto& Field : GameInstance->FieldDataArray)
        {
            if (Field.FieldName == FieldName)
            {
                for (auto& Area : Field.Areas)
                {
                    if (Area.AreaName == AreaName)
                    {
                        for (auto& SubjectGroup : Area.SubjectGroups)
                        {
                            if (SubjectGroup.SubjectGroupName == SubjectGroupName)
                            {
                                for (auto& Subject : SubjectGroup.Subjects)
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
                                                        for (auto& Subtopic : Topic.Subtopics)
                                                        {
                                                            // If a subtopic with the given name already exists, append the new content to it
                                                            if (Subtopic.Title == ElementName)
                                                            {
                                                                Subtopic.Content += ElementContent;
                                                                return;
                                                            }
                                                        }

                                                        // If no existing subtopic was found, create a new one
                                                        FSubtopic NewSubtopic;
                                                        NewSubtopic.Title = ElementName;
                                                        NewSubtopic.Content = ElementContent;
                                                        Topic.Subtopics.Add(NewSubtopic);
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    default:
        break;
    }
}




void UImportWidget::PopulateFieldComboBox(UComboBoxString* ComboBox)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		// Add FieldName to combo box
		ComboBox->AddOption(FieldData.FieldName);
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}



void UImportWidget::PopulateAreaComboBox(UComboBoxString* ComboBox, const FString& SelectedField)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		// Only add options for the selected field
		if (FieldData.FieldName == SelectedField)
		{
			// Loop through Areas in FieldData
			for (const FAreaStruct& AreaData : FieldData.Areas)
			{
				// Add AreaName to combo box
				ComboBox->AddOption(AreaData.AreaName);
			}

			// Found the selected field, no need to continue the loop
			break;
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}



void UImportWidget::PopulateSubjectGroupComboBox(UComboBoxString* ComboBox, const FString& SelectedArea)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			// Only add options for the selected area
			if (AreaData.AreaName == SelectedArea)
			{
				// Loop through SubjectGroups in AreaData
				for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
				{
					// Add SubjectGroupName to combo box
					ComboBox->AddOption(SubjectGroupData.SubjectGroupName);
				}

				// Found the selected area, no need to continue the loop
				break;
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UImportWidget::PopulateSubjectComboBox(UComboBoxString* ComboBox, const FString& SelectedSubjectGroup)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				// Only add options for the selected subject group
				if (SubjectGroupData.SubjectGroupName == SelectedSubjectGroup)
				{
					// Loop through Subjects in SubjectGroupData
					for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
					{
						// Add SubjectName to combo box
						ComboBox->AddOption(SubjectData.SubjectName);
					}

					// Found the selected subject group, no need to continue the loop
					break;
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UImportWidget::PopulateSectionComboBox(UComboBoxString* ComboBox, const FString& SelectedSubject)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
				{
					// Only add options for the selected subject
					if (SubjectData.SubjectName == SelectedSubject)
					{
						// Loop through SubjectDetailsArray in SubjectData
						for (const FSectionStruct& SectionData : SubjectData.SubjectDetailsArray)
						{
							// Add SectionName to combo box
							ComboBox->AddOption(SectionData.SectionName);
						}

						// Found the selected subject, no need to continue the loop
						break;
					}
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UImportWidget::PopulateTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedSection)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	bool bOptionAdded = false; // Variable to check if the option has been added

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		if (bOptionAdded) break; // Break if the option has been added

		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			if (bOptionAdded) break; // Break if the option has been added

			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				if (bOptionAdded) break; // Break if the option has been added

				for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
				{
					if (bOptionAdded) break; // Break if the option has been added

					for (const FSectionStruct& SectionData : SubjectData.SubjectDetailsArray)
					{
						// Only add options for the selected topic
						if (SectionData.SectionName == SelectedSection)
						{
							// Loop through Topics in SectionData
							for (const FTopic& TopicData : SectionData.Topics)
							{
								// Add Title to combo box
								ComboBox->AddOption(TopicData.Title);
							}

							bOptionAdded = true; // Set the variable to true

							// Found the selected topic, no need to continue the loop
							break;
						}
					}
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


void UImportWidget::PopulateSubTopicComboBox(UComboBoxString* ComboBox, const FString& SelectedTopic)
{
	// Get Game Instance and check if it's valid
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GameInstance || !ComboBox) return;

	// Clear the combo box first
	ComboBox->ClearOptions();

	bool bOptionAdded = false; // Variable to check if the option has been added

	// Loop through FieldDataArray
	for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
	{
		if (bOptionAdded) break; // Break if the option has been added

		for (const FAreaStruct& AreaData : FieldData.Areas)
		{
			if (bOptionAdded) break; // Break if the option has been added

			for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
			{
				if (bOptionAdded) break; // Break if the option has been added

				for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
				{
					if (bOptionAdded) break; // Break if the option has been added

					for (const FSectionStruct& SectionData : SubjectData.SubjectDetailsArray)
					{
						if (bOptionAdded) break; // Break if the option has been added

						for (const FTopic& TopicData : SectionData.Topics)
						{
							// Only add options for the selected topic
							if (TopicData.Title == SelectedTopic)
							{
								// Loop through Subtopics in TopicData
								for (const FSubtopic& SubtopicData : TopicData.Subtopics)
								{
									// Add Title to combo box
									ComboBox->AddOption(SubtopicData.Title);
								}

								bOptionAdded = true; // Set the variable to true

								// Found the selected topic, no need to continue the loop
								break;
							}
						}
					}
				}
			}
		}
	}

	// Refresh the combo box to show the new options
	ComboBox->RefreshOptions();
}


FString UImportWidget::ReadFileToString(FString FilePath)
{
    FString FileContents;
    if (!FFileHelper::LoadFileToString(FileContents, *FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load file: %s"), *FilePath);
        return TEXT("");
    }

    // Create an instance of AMyHttpClient
   HttpClient = NewObject<AMyHttpClient>(GetWorld());

    // Send the file content to the Python server
    //HttpClient->SendRequest("http://localhost:5000/process_text", "POST", FileContents, "text/plain");

    return FileContents;
}


