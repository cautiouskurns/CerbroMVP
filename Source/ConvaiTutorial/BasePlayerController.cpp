// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "TopicWidget.h"
#include "SectionWidget.h"
#include "SubTopicWidget.h"
#include "HUDWidgetTest.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include <Engine.h>



void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

}

    
USectionWidget* ABasePlayerController::CreateSectionWidget(const TArray<FTopic>& BlueprintTopicArray, const FSectionStruct& SectionData,
    TSubclassOf<UUserWidget> SectionWidgetClass, TSubclassOf<UUserWidget> TopicWidgetClass, TSubclassOf<UUserWidget> SubtopicWidgetClass, UHUDWidgetTest* InHUDTestWidget)
{
    HUDTestWidgetReference = InHUDTestWidget;

    if (SectionWidgetClass != nullptr)
    {
        USectionWidget* SectionWidget = CreateWidget<USectionWidget>(GetWorld(), SectionWidgetClass);

        if (SectionWidget)
        {
            //TArray<FSectionStruct> SectionData; 

            // Call CreateTopicWidgets function with the created SectionWidget
            CreateTopicWidgets(BlueprintTopicArray, SectionWidget, TopicWidgetClass, SubtopicWidgetClass);

            SectionWidget->SectionName = SectionData.SectionName;

            // Check if the cast was successful
            if (HUDTestWidgetReference)
            {
               HUDTestWidgetReference->AddSectionWidgetToHUD(SectionWidget);
            }

            return SectionWidget;
        }
    }

    return nullptr;
}


TArray<FSubtopic> ABasePlayerController::CreateTopicWidgets(const TArray<FTopic>& BlueprintTopicArray, USectionWidget* InSectionWidget, 
    TSubclassOf<UUserWidget> TopicWidgetClass, TSubclassOf<UUserWidget> SubtopicWidgetClass)
{
    SectionWidgetReference = InSectionWidget;
    SubtopicDataArray.Empty();

    for (const FTopic& TopicData : BlueprintTopicArray)
    {
        FString Title = TopicData.Title;

        UTopicWidget* TopicWidget = CreateWidget<UTopicWidget>(GetWorld(), TopicWidgetClass);

        if (TopicWidget)
        {
            UTopicWidget* CastedTopicWidget = Cast<UTopicWidget>(TopicWidget);

            if (CastedTopicWidget)
            {
                CastedTopicWidget->TopicName = TopicData.Title;
                CastedTopicWidget->Subtopics = TopicData.Subtopics;

                SectionWidgetReference->AddTopicWidget(CastedTopicWidget);
            }

            CreateSubTopicWidgets(TopicData.Subtopics, TopicWidget, SubtopicWidgetClass);

        }
    }
   return SubtopicDataArray;
}


void ABasePlayerController::CreateSubTopicWidgets(const TArray<FSubtopic>& SubTopics, UTopicWidget* TopicWidget,
    TSubclassOf<UUserWidget> SubtopicWidgetClass)
{

    if (TopicWidget)
    {
        // Implement the logic to create Subtopic widgets here
        // Add them to the SubtopicDataArray and the TopicWidget
        for (const FSubtopic& SubtopicData : SubTopics)
        {
            USubTopicWidget* SubtopicWidget = CreateWidget<USubTopicWidget>(GetWorld(), SubtopicWidgetClass);

            if (SubtopicWidget)
            {
                SubtopicWidget->Title = SubtopicData.Title;
                SubtopicWidget->Content = SubtopicData.Content;

                // Assuming UTopicWidget has a method to add a subtopic widget
                TopicWidget->AddSubTopicWidget(SubtopicWidget);

                // Add to the array
                SubtopicDataArray.Add(SubtopicData);
            }
        }
    }
}


void ABasePlayerController::RemoveAllChildrenFromWidget(UUserWidget* TargetWidget)
{
    if (TargetWidget)
    {
        // Cast to your specific widget class
        UHUDWidgetTest* MyUserWidget = Cast<UHUDWidgetTest>(TargetWidget);

        if (MyUserWidget && MyUserWidget->SectionBox)
        {
            TArray<UWidget*> ChildWidgets = MyUserWidget->SectionBox->GetAllChildren();
            for (UWidget* Widget : ChildWidgets)
            {
                if (Widget)
                {
                    Widget->RemoveFromParent();
                }
            }
        }
    }
}