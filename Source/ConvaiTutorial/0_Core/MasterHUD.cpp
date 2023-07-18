// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterHUD.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"
#include "ConvaiTutorial/BaseClasses/BasePlayerController.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "ConvaiTutorial/Widgets/InteractWidget.h"
#include "ConvaiTutorial/Widgets/SubjectWidget.h"
#include "ConvaiTutorial/Widgets/SubTopicWidget.h"


#include "ConvaiTutorial/HUDWidgetTest.h"

#include "Components/TextBlock.h"
#include "Components/ListView.h"



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