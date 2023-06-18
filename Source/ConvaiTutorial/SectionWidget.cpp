
// Fill out your copyright notice in the Description page of Project Settings.


#include "SectionWidget.h"
#include "TopicWidget.h"
#include "Components/VerticalBox.h"

void USectionWidget::AddTopicWidget(UTopicWidget* TopicWidget)
{
    if (TopicWidget && TopicsBox)
    {
        TopicsBox->AddChild(TopicWidget);
    }
}

void USectionWidget::OnSectionButtonClicked()
{
    // If the vertical box is currently visible, hide it, otherwise show it
    if (TopicsBox->Visibility == ESlateVisibility::Visible)
    {
        TopicsBox->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        TopicsBox->SetVisibility(ESlateVisibility::Visible);
    }
}