// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"


void UTestWidget::UpdateText(const FText& NewText, const FText& NewTitleText)
{
	if (TestTextBox)
	{
		TestTextBox->SetText(NewText);
	}

	if (TestTitleBox)
	{
		TestTitleBox->SetText(NewTitleText);
	}
}