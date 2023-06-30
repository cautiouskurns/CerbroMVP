// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterHUD.h"
#include "ReadWriteJsonFile.h"
#include "SubjectWidget.h"
#include "ListWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "BaseGameInstance.h"

void UMasterHUD::NativeConstruct()
{
    Super::NativeConstruct();

    if (ListWidget)
    {
        ListWidget->PopulateListView();
    }
}