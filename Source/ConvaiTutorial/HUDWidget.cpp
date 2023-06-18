// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "MasterTopicWidget.h"
#include "Components/VerticalBox.h"

void UHUDWidget::AddMasterTopicWidgetToHUD(UMasterTopicWidget* MasterTopicWidget)
{
	if (MasterTopicWidget && MasterTopicsBox)
	{
		MasterTopicsBox->AddChild(MasterTopicWidget);
	}
}
