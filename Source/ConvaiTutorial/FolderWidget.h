// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReadWriteJsonFile.h"
#include "SubjectWidget.h"
#include "BaseGameInstance.h"
#include "Components/TextBlock.h"
#include "FolderWidget.generated.h"

UCLASS()
class CONVAITUTORIAL_API UFolderWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FTreeViewItem Data;

    UFUNCTION(BlueprintCallable, Category = "Tree Widget")
    void SetItem(const FTreeViewItem& Item);

    void AddChild(UFolderWidget* Child);

    TArray<UObject*> GetChildren();

private:
    TMap<int32, UFolderWidget*> WidgetMap;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTreeView* SubjectTreeView;

    virtual void NativeConstruct() override;

private:
    void PopulateTreeView();
};