// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"

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