// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/TreeView.h"

#include "SubjectWidget.generated.h"

UCLASS()
class CONVAITUTORIAL_API USubjectWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //UFUNCTION(BlueprintCallable, Category = "Tree Widget")
    //void SetData(const FTreeViewItem& Item);

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UTextBlock* NameText;

};

