// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectoryWidget.h"
#include "FieldWidget.h"
#include "Components/VerticalBox.h"

void UDirectoryWidget::AddFieldWidget(UFieldWidget* FieldWidget)
{
    if (FieldBox != nullptr && FieldWidget != nullptr)
    {
        FieldBox->AddChild(FieldWidget);
    }
}