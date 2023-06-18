
// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterTopicWidget.h"
#include "Components/VerticalBox.h"

void UMasterTopicWidget::AddTopicWidget(UTopicWidget* TopicWidget)
{
    if (TopicWidget && TopicsBox)
    {
        TopicsBox->AddChild(TopicWidget);
    }
}
