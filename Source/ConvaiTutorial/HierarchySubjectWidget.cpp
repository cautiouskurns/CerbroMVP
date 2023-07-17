// Fill out your copyright notice in the Description page of Project Settings.


#include "HierarchySubjectWidget.h"
#include "Components/VerticalBox.h"
#include "ResourceWidget.h"

void UHierarchySubjectWidget::SetName(const FString& NewName)
{
	Name = NewName;
}

void UHierarchySubjectWidget::AddChildWidget(UResourceWidget* NewChildWidget)
{
	ChildWidgets.Add(NewChildWidget);
}

void UHierarchySubjectWidget::AddResourcesWidget(UResourceWidget* ResourcesWidget)
{
    if (ResourcesBox != nullptr && ResourcesWidget != nullptr)
    {
        ResourcesBox->AddChild(ResourcesWidget);
    }
}

void UHierarchySubjectWidget::OnHierarchySubjectButtonClicked()
{
    // If the vertical box is currently visible, hide it, otherwise show it
    if (ResourcesBox->Visibility == ESlateVisibility::Visible)
    {
        ResourcesBox->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        ResourcesBox->SetVisibility(ESlateVisibility::Visible);
    }
}