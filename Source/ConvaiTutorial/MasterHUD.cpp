// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterHUD.h"
#include "ReadWriteJsonFile.h"
#include "SubjectWidget.h"
#include "SubTopicWidget.h"
#include "HUDWidgetTest.h"
#include "BasePlayerController.h"
#include "InteractWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "BaseGameInstance.h"

void UMasterHUD::NativeConstruct()
{
    Super::NativeConstruct();

    // Assuming you've set the variable name of the UInteractWidget in your blueprint to "InteractWidget"
    UInteractWidget* InteractWidget = Cast<UInteractWidget>(GetWidgetFromName(TEXT("InteractWidget")));

    if (InteractWidget)
    {
        ABasePlayerController* PC = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
        if (PC)
        {
            PC->SetInteractWidget(InteractWidget);
        }
    }
}