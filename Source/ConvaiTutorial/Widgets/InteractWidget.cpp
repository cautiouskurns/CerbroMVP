// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include <Components/ComboBoxString.h>
#include <Kismet/GameplayStatics.h>


void UInteractWidget::UpdateText(const FString& NewText, const FString& NewTextTitle)
{
    if (SubTopicTitleText)
    {
        SubTopicTitleText->SetText(FText::FromString(NewTextTitle));
    }

    if (SubTopicContentText)
    {
        SubTopicContentText->SetText(FText::FromString(NewText));
    }
}



void UInteractWidget::PopulateFieldComboBox(UComboBoxString* ComboBox)
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



void UInteractWidget::PopulateAreaComboBox(UComboBoxString* ComboBox, const FString& SelectedField)
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



void UInteractWidget::PopulateSubjectGroupComboBox(UComboBoxString* ComboBox, const FString& SelectedArea)
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


void UInteractWidget::PopulateSubjectComboBox(UComboBoxString* ComboBox, const FString& SelectedSubjectGroup)
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


void UInteractWidget::PopulateSectionComboBox(UComboBoxString* ComboBox, const FString& SelectedSubject)
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