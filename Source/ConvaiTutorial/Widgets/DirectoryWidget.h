// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/Widgets/FieldWidget.h"

#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"

#include "DirectoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UDirectoryWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UVerticalBox* FieldBox;

	void AddFieldWidget(UFieldWidget* FieldWidget);

};
