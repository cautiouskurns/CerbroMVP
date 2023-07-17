// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"
#include "BaseGameInstance.h"
#include "ReadWriteJsonFile.h"
#include "Components/Button.h"
#include <Components/Button.h>
#include "Components/TextBlock.h"

void UResourceWidget::SetName(const FString& NewName)
{
	Name = NewName;
}

void UResourceWidget::NativeConstruct()
{
    Super::NativeConstruct();

    MyButton = WidgetTree->FindWidget<UButton>(FName("SubjectResourceButton"));


    // assuming MyButton is a UButton* property and it's been properly initialized
    if (MyButton)
    {
        // bind the OnClicked event to the ButtonClicked function
        MyButton->OnClicked.AddDynamic(this, &UResourceWidget::ButtonClicked);
    }
}

void UResourceWidget::ButtonClicked()
{
    FString TargetSubjectName = this->AssociatedSubject.SubjectName;  // Assuming you have stored the SubjectName in the Widget

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance)
    {
        for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
        {
            for (const FAreaStruct& AreaData : FieldData.Areas)
            {
                for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
                {
                    for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
                    {
                        if (SubjectData.SubjectName == TargetSubjectName)
                        {
                            // You found the subject data you're looking for.
                            // Do something with SubjectData
                            break;
                        }
                    }
                }
            }
        }
    }
}

int32 UResourceWidget::FindMatchingSubjectIndex()
{
    FString TargetSubjectName = this->AssociatedSubject.SubjectName;  // Assuming you have stored the SubjectName in the Widget

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance)
    {
        int32 FieldIndex = 0;
        for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
        {
            int32 AreaIndex = 0;
            for (const FAreaStruct& AreaData : FieldData.Areas)
            {
                int32 SubjectGroupIndex = 0;
                for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
                {
                    int32 SubjectIndex = 0;
                    for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
                    {
                        if (SubjectData.SubjectName == TargetSubjectName)
                        {
                            // Found the subject data you're looking for.
                            // Return the subject index.
                            return SubjectIndex;
                        }
                        SubjectIndex++;
                    }
                    SubjectGroupIndex++;
                }
                AreaIndex++;
            }
            FieldIndex++;
        }
    }

    // Subject not found, return an invalid index.
    return -1;
}