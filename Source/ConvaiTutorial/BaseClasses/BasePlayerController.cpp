// Fill out your copyright notice in the Description page of Project Settings.



#include "BasePlayerController.h"

#include "ConvaiTutorial/BaseClasses/CoreGameMode.h"
#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"
#include "ConvaiTutorial/VoiceCommandManagement/VoiceController.h"

#include "ConvaiTutorial/GraphManagement/NodeManager.h"
#include "ConvaiTutorial/GraphManagement/NodeActorBase.h"

#include "ConvaiTutorial/Widgets/DirectoryHierarchyManager.h"
#include "ConvaiTutorial/Widgets/TopicWidget.h"
#include "ConvaiTutorial/Widgets/SectionWidget.h"
#include "ConvaiTutorial/Widgets/SubTopicWidget.h"
#include "ConvaiTutorial/Widgets/FieldWidget.h"
#include "ConvaiTutorial/Widgets/AreaWidget.h"
#include "ConvaiTutorial/Widgets/SubjectWidget.h"
#include "ConvaiTutorial/Widgets/ResourceWidget.h"
#include "ConvaiTutorial/Widgets/DirectoryWidget.h"
#include "ConvaiTutorial/Widgets/InteractWidget.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetTree.h"
#include <Engine.h>

#include <Blueprint/WidgetBlueprintLibrary.h>


#include "Kismet/GameplayStatics.h"

#include "ConvaiTutorial/HUDWidgetTest.h"
#include "ConvaiTutorial/Testwidget.h"





void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

    UWorld* World = GetWorld();
    UBaseGameInstance* GameInstance = World ? Cast<UBaseGameInstance>(World->GetGameInstance()) : nullptr;

    VoiceControllerInstance = NewObject<UVoiceController>();
    VoiceControllerInstance->Init(GameInstance);
    VoiceControllerInstance->PlayerControllerRef = this;

//     VoiceControllerInstance = NewObject<UVoiceController>();
//     VoiceControllerInstance->PlayerControllerRef = this;

// UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);

    ACharacter* MyCharacter = nullptr;
    if (World)
    {
        MyCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
    }
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

void ABasePlayerController::RemoveAllChildrenFromDirectoryWidget(UUserWidget* TargetWidget)
{
    if (TargetWidget)
    {
        // Cast to your specific widget class
        UDirectoryWidget* MyUserWidget = Cast<UDirectoryWidget>(TargetWidget);

        if (MyUserWidget && MyUserWidget->FieldBox)
        {
            TArray<UWidget*> ChildWidgets = MyUserWidget->FieldBox->GetAllChildren();
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

    for (int32 FieldIndex = 0; FieldIndex < FieldDataArray.Num(); ++FieldIndex)
    {
        const FFieldStruct& FieldData = FieldDataArray[FieldIndex];
        UFieldWidget* FieldWidget = CreateWidget<UFieldWidget>(GetWorld(), FieldWidgetClass);

        if (FieldWidget)
        {
            FieldWidget->SetName(FieldData.FieldName);
            CreateAreaWidgets(FieldData.Areas, FieldWidget, AreaWidgetClass, SubjectWidgetClass, ResourceWidgetClass, FieldIndex);

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
    TSubclassOf<UResourceWidget> ResourceWidgetClass,
    int32 FieldIndex)
{
    FieldWidgetReference = ParentWidget;

    for (int32 AreaIndex = 0; AreaIndex < AreaDataArray.Num(); ++AreaIndex)
    {
        const FAreaStruct& AreaData = AreaDataArray[AreaIndex];
        UAreaWidget* AreaWidget = CreateWidget<UAreaWidget>(GetWorld(), AreaWidgetClass);
        if (AreaWidget)
        {
            AreaWidget->SetName(AreaData.AreaName);
            CreateSubjectGroupWidgets(AreaData.SubjectGroups, AreaWidget, SubjectWidgetClass, ResourceWidgetClass, FieldIndex, AreaIndex);
            ParentWidget->AddChildWidget(AreaWidget);

            if (FieldWidgetReference)
            {
                FieldWidgetReference->AddAreaWidget(AreaWidget);
            }
        }
    }
}


void ABasePlayerController::CreateSubjectGroupWidgets(
    const TArray<FSubjectGroupStruct>& SubjectDataArray,
    UAreaWidget* ParentWidget,
    TSubclassOf<UHierarchySubjectWidget> SubjectWidgetClass,
    TSubclassOf<UResourceWidget> ResourceWidgetClass,
    int32 FieldIndex,
    int32 AreaIndex)
{
    AreaWidgetReference = ParentWidget;

    for (int32 SubjectGroupIndex = 0; SubjectGroupIndex < SubjectDataArray.Num(); ++SubjectGroupIndex)
    {
        const FSubjectGroupStruct& SubjectData = SubjectDataArray[SubjectGroupIndex];
        UHierarchySubjectWidget* SubjectWidget = CreateWidget<UHierarchySubjectWidget>(GetWorld(), SubjectWidgetClass);
        if (SubjectWidget)
        {
            SubjectWidget->SetName(SubjectData.SubjectGroupName);
            CreateSubjectWidgets(SubjectData.Subjects, SubjectWidget, ResourceWidgetClass, FieldIndex, AreaIndex, SubjectGroupIndex);
            ParentWidget->AddChildWidget(SubjectWidget);

            if (AreaWidgetReference)
            {
                AreaWidgetReference->AddHierarchySubjectWidget(SubjectWidget);
            }
        }
    }
}

void ABasePlayerController::CreateSubjectWidgets(
    const TArray<FSubjectStruct>& ResourceDataArray,
    UHierarchySubjectWidget* ParentWidget,
    TSubclassOf<UResourceWidget> ResourceWidgetClass,
    int32 FieldIndex,
    int32 AreaIndex,
    int32 SubjectGroupIndex)
{
    HierarchySubjectWidgetReference = ParentWidget;

    for (const FSubjectStruct& ResourceData : ResourceDataArray)
    {
        UResourceWidget* ResourceWidget = CreateWidget<UResourceWidget>(GetWorld(), ResourceWidgetClass);
        ResourceWidget->AssociatedSubject.SubjectName = ResourceData.SubjectName;


        // Pass the indices to the ResourceWidget
        ResourceWidget->FieldIndex = FieldIndex;
        ResourceWidget->AreaIndex = AreaIndex;
        ResourceWidget->SubjectGroupIndex = SubjectGroupIndex;

        if (ResourceWidget)
        {

            ResourceWidget->SetName(ResourceData.SubjectName);
            ParentWidget->AddChildWidget(ResourceWidget);

            if (AreaWidgetReference)
            {
                HierarchySubjectWidgetReference->AddResourcesWidget(ResourceWidget);
            }
        }
    }
}




void ABasePlayerController::OnButtonClicked(UResourceWidget* ClickedWidget)
{
    if (ClickedWidget)
    {
        FString TargetSubjectName = ClickedWidget->AssociatedSubject.SubjectName;
        FSubjectStruct FoundSubject = FindSubjectByName(TargetSubjectName);

        // Do something with FoundSubject
    }
}


FSubjectStruct ABasePlayerController::FindSubjectByName(FString TargetSubjectName)
{
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance)
    {
        for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
        {
            for (const FAreaStruct& AreaData : FieldData.Areas)
            {
                for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
                {
                    for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
                    {
                        if (SubjectData.SubjectName == TargetSubjectName)
                        {
                            // You found the subject data you're looking for.
                            // Return the subject data
                            return SubjectData;
                        }
                    }
                }
            }
        }
    }

    // If no subject with the given name is found, return an empty FSubjectStruct
    return FSubjectStruct();
}
//
//FString ABasePlayerController::PrintContentForVoicePrompt(FString VoicePrompt)
//{
//    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
//    if (GameInstance)
//    {
//        // Traverse the field data array
//        for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
//        {
//            // Traverse the areas within each field
//            for (const FAreaStruct& AreaData : FieldData.Areas)
//            {
//                // Traverse the subject groups within each area
//                for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
//                {
//                    // Traverse the subjects within each subject group
//                    for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
//                    {
//                        // Check if the subject's name matches the voice prompt
//                        //if (SubjectData.SubjectName == VoicePrompt)
//                        if (SubjectData.SubjectName.Contains(VoicePrompt, ESearchCase::IgnoreCase))
//                        {
//                            // We've found the desired topic, now we can print its content
//                            if (GEngine)
//                            {
//                                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Content function: %s"), *SubjectData.SubjectName));
//                            }
//                            UpdateTextWidget(SubjectData.SubjectName);
//
//                            return SubjectData.SubjectName;
//                        }
//                    
//                    }
//                }
//            }
//        }
//    }
//    return FString();
//    // If we've gotten this far, the voice prompt did not match any subject
//    UE_LOG(LogTemp, Warning, TEXT("No content found for voice prompt: %s"), *VoicePrompt);
//}
//
//
//
//FSubjectStruct ABasePlayerController::FindSubjectByVocalPrompt(FString SubjectName)
//{
//    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
//    if (GameInstance)
//    {
//        for (const FFieldStruct& FieldData : GameInstance->FieldDataArray)
//        {
//            for (const FAreaStruct& AreaData : FieldData.Areas)
//            {
//                for (const FSubjectGroupStruct& SubjectGroupData : AreaData.SubjectGroups)
//                {
//                    for (const FSubjectStruct& SubjectData : SubjectGroupData.Subjects)
//                    {
//                        if (SubjectData.SubjectName.Contains(SubjectName, ESearchCase::IgnoreCase))
//                        {
//                            return SubjectData;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return FSubjectStruct(); // Return an empty/default FSubjectStruct if no match found
//}
//
//
//void ABasePlayerController::RetrieveSectionsForSubject(FString SubjectName)
//{
//    // Retrieve the subject based on the SubjectName
//    FSubjectStruct SubjectData = FindSubjectByVocalPrompt(SubjectName);
//
//    // We no longer need the if (SubjectData) check here, because we're working with values directly,
//    // not pointers. If there's no matching subject, SubjectData will be an empty/default FSubjectStruct.
//
//    for (const FSectionStruct& Section : SubjectData.SubjectDetailsArray)
//    {
//        OnSectionFound(Section.SectionName);
//        RetrieveTopicsForSection(Section);
//    }
//}
//
//void ABasePlayerController::RetrieveTopicsForSection(const FSectionStruct& SectionData)
//{
//    for (const FTopic& Topic : SectionData.Topics)
//    {
//        OnTopicFound(Topic.Title);
//        RetrieveSubtopicsForTopic(Topic);
//    }
//}
//
//void ABasePlayerController::RetrieveSubtopicsForTopic(const FTopic& TopicData)
//{
//    for (const FSubtopic& Subtopic : TopicData.Subtopics)
//    {
//        OnSubtopicFound(Subtopic.Title);
//    }
//}
//
//
//void ABasePlayerController::ClearContentForVoicePrompt(FString VoicePrompt)
//{
//    if (VoicePrompt.Contains("Clear", ESearchCase::IgnoreCase))
//    {
//        // pritn to screen that content is cleared
//        if (GEngine)
//        {
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Content cleared")));
//		}
//        OnClearContent();
//    }
//}