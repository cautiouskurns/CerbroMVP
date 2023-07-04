// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Engine/GameInstance.h"
#include "ImportWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UImportWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "File Operations")
	FString OpenDialogForFile();

	UFUNCTION(BlueprintCallable, Category = "File")
	FString LoadJsonAsString(FString FilePath);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	FString SelectedFilePath;
	
};
