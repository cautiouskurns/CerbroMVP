// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaWidget.h"

#include "ConvaiTutorial/Widgets/HierarchySubjectWidget.h"

#include "Components/VerticalBox.h"


void UAreaWidget::SetName(const FString& NewName)
{
	Name = NewName;
}

void UAreaWidget::AddChildWidget(UHierarchySubjectWidget* NewChildWidget)
{
	ChildWidgets.Add(NewChildWidget);
}

void UAreaWidget::AddHierarchySubjectWidget(UHierarchySubjectWidget* HierarchySubjectWidget)
{
    if (HierarchySubjectBox != nullptr && HierarchySubjectWidget != nullptr)
    {
        HierarchySubjectBox->AddChild(HierarchySubjectWidget);
    }
}

void UAreaWidget::OnAreaButtonClicked()
{
    // If the vertical box is currently visible, hide it, otherwise show it
    if (HierarchySubjectBox->Visibility == ESlateVisibility::Visible)
    {
        HierarchySubjectBox->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        HierarchySubjectBox->SetVisibility(ESlateVisibility::Visible);
    }
}