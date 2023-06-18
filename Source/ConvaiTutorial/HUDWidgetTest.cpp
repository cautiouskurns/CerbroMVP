// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidgetTest.h"
#include "SectionWidget.h"
#include "Components/VerticalBox.h"

void UHUDWidgetTest::AddSectionWidgetToHUD(USectionWidget* SectionWidget)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Created Section Widget!"));

	//UE_LOG(LogTemp, Warning, TEXT("Created Section Widget"));

	if (SectionWidget && SectionBox)
	{
		SectionBox->AddChild(SectionWidget);
	}
}