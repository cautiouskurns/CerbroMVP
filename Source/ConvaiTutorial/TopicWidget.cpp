// Fill out your copyright notice in the Description page of Project Settings.

#include "TopicWidget.h"
#include "SubTopicWidget.h"
#include "Components/VerticalBox.h"

void UTopicWidget::OnTopicButtonClicked()
{
    // If the vertical box is currently visible, hide it, otherwise show it
    if (SubtopicsBox->Visibility == ESlateVisibility::Visible)
    {
        SubtopicsBox->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        SubtopicsBox->SetVisibility(ESlateVisibility::Visible);
    }
}

// Test comment

void UTopicWidget::AddSubTopicWidget(USubTopicWidget* SubTopicWidget)
{
    if (SubTopicWidget && SubtopicsBox)
    {
		SubtopicsBox->AddChild(SubTopicWidget);
	}
}
