// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

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

}


TArray<int32> UResourceWidget::FindMatchingIndices()
{
    FString TargetSubjectName = this->AssociatedSubject.SubjectName;  // Assuming you have stored the SubjectName in the Widget

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance)
    {
        int32 FieldIndex2 = 0;
        for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
        {
            int32 AreaIndex2 = 0;
            for (const FAreaStruct& AreaData : FieldData.Areas)
            {
                int32 SubjectGroupIndex2 = 0;
                for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
                {
                    int32 SubjectIndex2 = 0;
                    for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
                    {
                        if (SubjectData.SubjectName == TargetSubjectName)
                        {
                            // Found the subject data you're looking for.
                            // Return the indices.
                            return { FieldIndex2, AreaIndex2, SubjectGroupIndex2, SubjectIndex2 };
                        }
                        SubjectIndex2++;
                    }
                    SubjectGroupIndex2++;
                }
                AreaIndex2++;
            }
            FieldIndex2++;
        }
    }

    // Subject not found, return an invalid indices.
    return { -1, -1, -1, -1 };
}


