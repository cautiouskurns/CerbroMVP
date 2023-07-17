// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldWidget.h"
#include "AreaWidget.h"
#include "Components/VerticalBox.h"

void UFieldWidget::SetName(const FString& NewName)
{
    Name = NewName;
}

void UFieldWidget::AddChildWidget(UAreaWidget* NewChildWidget)
{
    ChildWidgets.Add(NewChildWidget);
}

void UFieldWidget::AddAreaWidget(UAreaWidget* AreaWidget)
{
    if (AreaBox != nullptr && AreaWidget != nullptr)
    {
        AreaBox->AddChild(AreaWidget);
    }
}

void UFieldWidget::OnFieldButtonClicked()
{
    // If the vertical box is currently visible, hide it, otherwise show it
    if (AreaBox->Visibility == ESlateVisibility::Visible)
    {
        AreaBox->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        AreaBox->SetVisibility(ESlateVisibility::Visible);
    }
}