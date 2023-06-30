// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TreeView.h"
#include "FolderWidget.h"
#include "ListWidget.generated.h"
#include "MasterHUD.generated.h"


/**
 * 
 */

UCLASS()
class CONVAITUTORIAL_API UMasterHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    UListWidget* ListWidget;
};