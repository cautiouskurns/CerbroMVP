// Fill out your copyright notice in the Description page of Project Settings.


#include "ListWidget.h"
#include "BaseGameInstance.h"
#include "ItemWidget.h"
#include "ListViewItemBase.h"
#include "Components/TextBlock.h"


void UListWidget::PopulateListView()
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance && ItemListView)
    {
        TArray<FListViewItem> ListData = GameInstance->GetListData();

        for (const FListViewItem& Item : ListData) e
        {
            UItemWidget* NewWidget = CreateWidget<UItemWidget>(this, UItemWidget::StaticClass());
            NewWidget->SetData(Item);
            ItemListView->AddChild(NewWidget);
        }
    }
}