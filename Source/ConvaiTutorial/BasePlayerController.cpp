// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "TopicWidget.h"
#include "SectionWidget.h"
#include "SubTopicWidget.h"
#include "NodeManager.h"
#include "GraphManagement/NodeActorBase.h"
#include "CoreGameMode.h"
#include "HUDWidgetTest.h"
#include "BaseGameInstance.h"
#include "Testwidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include <Engine.h>
#include "DirectoryHierarchyManager.h"
#include "FieldWidget.h"
#include "AreaWidget.h"
#include "SubjectWidget.h"
#include "ResourceWidget.h"
#include "DirectoryWidget.h"
#include "GraphManagement/NodeActorBase.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "InteractWidget.h"





void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

}


void ABasePlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // If we're moving to a node, gradually move and rotate the pawn towards the target position and orientation
    if (bMovingToNode)
    {
        APawn* ControlledPawn = GetPawn();
        if (ControlledPawn != nullptr)
        {
            FVector CurrentPosition = ControlledPawn->GetActorLocation();
            FRotator CurrentOrientation = ControlledPawn->GetActorRotation();

            FVector NewPosition = FMath::VInterpTo(CurrentPosition, TargetPosition, DeltaTime, 0.5f); // adjust the speed as needed
            FRotator NewOrientation = FMath::RInterpTo(CurrentOrientation, TargetOrientation, DeltaTime, 0.5f); // adjust the speed as needed

            ControlledPawn->SetActorLocationAndRotation(NewPosition, NewOrientation);

            // If we're close enough to the target position and orientation, stop moving
            if (FVector::DistSquared(NewPosition, TargetPosition) < FMath::Square(100.0f) // adjust the tolerance as needed
                && FMath::Abs((NewOrientation - TargetOrientation).GetNormalized().Yaw) < 1.0f) // adjust the tolerance as needed
            {
                bMovingToNode = false;
            }
        }
    }
}


void ABasePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Bind the OnLeftMouseClick function to the left mouse button click event
    InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ABasePlayerController::OnRightMouseClick);
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

    



void ABasePlayerController::MoveCameraToNode(ANodeActorBase* Node)
{
   
    // Store the target position and orientation as member variables
    TargetPosition = Node->GetActorLocation() - FVector(0, 500, -500); // adjust this as needed
    TargetOrientation = (Node->GetActorLocation() - TargetPosition).Rotation();

    // Set a flag to indicate that we're moving to a node
    bMovingToNode = true;

}


void ABasePlayerController::SetInteractWidget(UInteractWidget* NewWidget)
{
    InteractWidget = NewWidget;
}





void ABasePlayerController::OnRightMouseClick()
{
    // Perform a raycast under the cursor
    FHitResult HitResult;
    GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);

    // If the raycast hit a node, move the camera to that node
    AActor* HitActor = HitResult.GetActor();

    if (HitActor != nullptr && HitActor->IsA<ANodeActorBase>())
    {
        ANodeActorBase* NodeActorBase = Cast<ANodeActorBase>(HitActor);
        if (NodeActorBase)  // Check that NodeActorBase is not null
        {
            MoveCameraToNode(NodeActorBase);

            LastClickedNodeContent = NodeActorBase->SubtopicContent;

            LastClickedNodeTitle = NodeActorBase->SubtopicTitle;

            // Trigger the delegate
            OnRightMouseClickedDelegate.Broadcast();

        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NodeActorBase is null"));
        }

    }

}


void ABasePlayerController::TestDataTable(FName RowName)
{
    // Replace "PathToYourDataTable" with the path to your data table
    UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Data/DT_ImageTestData.DT_ImageTestData'")));
   
    // Check if the data table was loaded
    if (!DataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("Data table not found"));
        return;
    }

    // Get a row from the data table
    FImageTestStruct* Row = DataTable->FindRow<FImageTestStruct>(RowName, TEXT(""));

    // Check if the row was found
    if (!Row)
    {
        UE_LOG(LogTemp, Error, TEXT("Row not found in data table"));
        return;
    }

    // Print the fields of the row
    // print row name and texture name to screen using engine function
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Row->ImageName);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Row->TestTexture->GetName());

}






void ABasePlayerController::CreateDirectoryHierarchyWidgets(
    const TArray<FFieldStruct>& FieldDataArray,
    TSubclassOf<UFieldWidget> FieldWidgetClass,
    TSubclassOf<UAreaWidget> AreaWidgetClass,
    TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass,
    TSubclassOf<UResourceWidget> ResourceWidgetClass,
    UDirectoryWidget* MainUIDirectory)
{
    DirectoryWidgetReference = MainUIDirectory;

    for (const FFieldStruct& FieldData : FieldDataArray)
    {
        UFieldWidget* FieldWidget = CreateWidget<UFieldWidget>(GetWorld(), FieldWidgetClass);

        if (FieldWidget)
        {
            FieldWidget->SetName(FieldData.Name);
            CreateAreaWidgets(FieldData.Areas, FieldWidget, AreaWidgetClass, SubjectWidgetClass, ResourceWidgetClass);

            // Add FieldWidget to the main UI
            if (MainUIDirectory != nullptr)
            {
                MainUIDirectory->AddFieldWidget(FieldWidget);
            }

            // Check if the cast was successful
            if (DirectoryWidgetReference)
            {
                DirectoryWidgetReference->AddFieldWidget(FieldWidget);
            }
        }
    }
}


void ABasePlayerController::CreateAreaWidgets(
    const TArray<FAreaStruct>& AreaDataArray,
    UFieldWidget* ParentWidget,
    TSubclassOf<UAreaWidget> AreaWidgetClass,
    TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass,
    TSubclassOf<UResourceWidget> ResourceWidgetClass)
{
    FieldWidgetReference = ParentWidget;

    for (const FAreaStruct& AreaData : AreaDataArray)
    {
        UAreaWidget* AreaWidget = CreateWidget<UAreaWidget>(GetWorld(), AreaWidgetClass);
        if (AreaWidget)
        {
            AreaWidget->SetName(AreaData.Name);
            CreateSubjectWidgets(AreaData.Subjects, AreaWidget, SubjectWidgetClass, ResourceWidgetClass);
            ParentWidget->AddChildWidget(AreaWidget);

            if (FieldWidgetReference)
            {
                FieldWidgetReference->AddAreaWidget(AreaWidget);
            }
        }
    }
}


void ABasePlayerController::CreateSubjectWidgets(
    const TArray<FHierarchySubjectStruct>& SubjectDataArray,
    UAreaWidget* ParentWidget,
    TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass,
    TSubclassOf<UResourceWidget> ResourceWidgetClass)
{
    AreaWidgetReference = ParentWidget;

    for (const FHierarchySubjectStruct& SubjectData : SubjectDataArray)
    {
        UHierarchySubjectWidget* SubjectWidget = CreateWidget<UHierarchySubjectWidget>(GetWorld(), SubjectWidgetClass);
        if (SubjectWidget)
        {
            SubjectWidget->SetName(SubjectData.Name);
            CreateResourceWidgets(SubjectData.Resources, SubjectWidget, ResourceWidgetClass);
            ParentWidget->AddChildWidget(SubjectWidget);

            if (AreaWidgetReference)
            {
                AreaWidgetReference->AddHierarchySubjectWidget(SubjectWidget);
            }
        }
    }
}

void ABasePlayerController::CreateResourceWidgets(
    const TArray<FResourceStruct>& ResourceDataArray,
    UHierarchySubjectWidget* ParentWidget,
    TSubclassOf<UResourceWidget> ResourceWidgetClass)
{
    HierarchySubjectWidgetReference = ParentWidget;

    for (const FResourceStruct& ResourceData : ResourceDataArray)
    {
        UResourceWidget* ResourceWidget = CreateWidget<UResourceWidget>(GetWorld(), ResourceWidgetClass);
        if (ResourceWidget)
        {
            ResourceWidget->SetName(ResourceData.Name);
            ParentWidget->AddChildWidget(ResourceWidget);

            if (AreaWidgetReference)
            {
                HierarchySubjectWidgetReference->AddResourcesWidget(ResourceWidget);
            }
        }
    }
}