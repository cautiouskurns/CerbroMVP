// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeManager.h"
#include "NodeActorBase.h"
#include "ReadWriteJsonFile.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "BaseGameInstance.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ANodeManager::ANodeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   /* StartPosition = FVector(-2230.000000, -360.000000, 0);*/
    StartPosition = FVector(0, 0, 0);

}

// Called when the game starts or when spawned
void ANodeManager::BeginPlay()
{
	Super::BeginPlay();

    // This ensures that the nodes and edges are created after the GameInstance data is populated
    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ANodeManager::InitializeNodesByTopic);
}

// Called every frame
void ANodeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANodeManager::InitializeNodes()
{
    UWorld* World = GetWorld();
    if (!World) return;

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GameInstance) return;

    TArray<FSectionStruct> GameInstanceSectionDataArray = GameInstance->SectionDataArray;
    TArray<FSubtopic> GameInstanceSubTopicDataArray = GameInstance->SubTopicStructArray;


    FString TestContent = GameInstanceSectionDataArray[0].Topics[0].Subtopics[0].Title;
    UE_LOG(LogTemp, Warning, TEXT("TestContent: %s"), *TestContent);

    int TotalSubTopics = 0;


    if (GameInstance)
    {
        for (FSectionStruct& Section : GameInstance->SectionDataArray)
        {
            for (FTopic& Topic : Section.Topics)
            {
                TotalSubTopics += Topic.Subtopics.Num();
            }
        }
        // Now TotalSubTopics contains the total number of subtopics

        // pritn TotalSubTopics
        UE_LOG(LogTemp, Warning, TEXT("TotalSubTopics: %d"), TotalSubTopics);
    }

    
    for (int i = 0; i < TotalSubTopics; ++i)  // Create 10 nodes
    {
        FActorSpawnParameters SpawnParams;

        if (NodeBlueprintClass)
        {
            ANodeActorBase* NodeActor = World->SpawnActor<ANodeActorBase>(NodeBlueprintClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
            NodeActors.Add(NodeActor);

            UE_LOG(LogTemp, Warning, TEXT("Node spawned!"));
        }
        else
        {
			UE_LOG(LogTemp, Warning, TEXT("NodeBlueprintClass is null!"));
		}

    }
}



void ANodeManager::PositionNodes()
{
    int32 size = FMath::RoundToInt(FMath::Sqrt(static_cast<float>(NodeActors.Num())));  // the number of nodes along one edge of the grid
    float spacing = 1000.f / size;  // the distance between each node

    for (int32 i = 0; i < NodeActors.Num(); i++)
    {
        AActor* NodeActor = NodeActors[i];
        if (!NodeActor) continue;  // skip if the pointer is null

        FVector Position;

        // Print position
        Position.X = (i % size) * spacing;
        Position.Y = (i / size) * spacing;
        Position.Z = 0;

        NodeActor->SetActorLocation(Position + StartPosition);
       
    }

    // Set Node Text
    SetNodeText();
}


TArray<FString> ANodeManager::GenerateSubtopicNames()
{
    TArray<FString> SubTopicNames;
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());

    if (GameInstance)
    {
        // First, flatten the structure into a list of subtopic names
        for (FSectionStruct& Section : GameInstance->SectionDataArray)
        {
            for (FTopic& Topic : Section.Topics)
            {
                for (FSubtopic& SubTopic : Topic.Subtopics)
                {
                    SubTopicNames.Add(SubTopic.Title);
                }
            }
        }
    }

    return SubTopicNames;
}


void ANodeManager::SetNodeText()
{
    TArray<FString> SubTopicNames = GenerateSubtopicNames();

    for (int32 i = 0; i < NodeActors.Num(); i++)
    {
        AActor* NodeActor = NodeActors[i];
        if (!NodeActor) continue;  // skip if the pointer is null

        ANodeActorBase* NodeActorBase = Cast<ANodeActorBase>(NodeActor);
        if (NodeActorBase && i < SubTopicNames.Num())
        {
            NodeActorBase->SetNodeText(SubTopicNames[i]);
        }
    }
}


void ANodeManager::GenerateEdges()
{
    // Ensure the world exists
    UWorld* World = GetWorld();
    if (!World) return;

    // Ensure the Edge blueprint class is set
    if (!EdgeBlueprintClass) return;

    // Spawn params
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    for (int32 i = 0; i < NodeActors.Num(); i++)
    {
        for (int32 j = i + 1; j < NodeActors.Num(); j++)
        {
            // Create edge between NodeActors[i] and NodeActors[j]
            AEdgeActorBase* EdgeActor = World->SpawnActor<AEdgeActorBase>(EdgeBlueprintClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
            if (EdgeActor)
            {
                EdgeActor->SetNodes(NodeActors[i], NodeActors[j]);
                EdgeActors.Add(EdgeActor);
            }
        }
    }
}







//void ANodeManager::InitializeNodesByTopic()
//{
//    UWorld* World = GetWorld();
//    if (!World) return;
//
//    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//    if (!GameInstance) return;
//
//    TArray<FSectionStruct> GameInstanceSectionDataArray = GameInstance->SectionDataArray;
//
//    // Generate Nodes for Topics and Subtopics
//    int32 TopicIndex = 0;
//    for (const FSectionStruct& Section : GameInstanceSectionDataArray)
//    {
//        for (const FTopic& Topic : Section.Topics)
//        {
//            // Create a node for the Topic
//            ANodeActorBase* TopicNode = CreateNode(Topic.Title, CalculateTopicPosition(TopicIndex));
//            NodeActors.Add(TopicNode);
//            TopicIndex++;
//
//            // Create a node for each Subtopic
//            int32 SubtopicIndex = 0;
//            for (const FSubtopic& Subtopic : Topic.Subtopics)
//            {
//                ANodeActorBase* SubtopicNode = CreateNode(Subtopic.Title, CalculateSubTopicPosition(TopicIndex, SubtopicIndex));
//                NodeActors.Add(SubtopicNode);
//
//                CreateEdge(TopicNode, SubtopicNode);
//
//                SubtopicIndex++;
//            }
//        }
//    }
//}

void ANodeManager::InitializeNodesByTopic()
{
    UWorld* World = GetWorld();
    if (!World) return;

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GameInstance) return;

    TArray<FSectionStruct> GameInstanceSectionDataArray = GameInstance->SectionDataArray;

    // Determine total number of topics across all sections
    int32 TotalNumberOfTopics = 0;
    for (const FSectionStruct& Section : GameInstanceSectionDataArray)
    {
        TotalNumberOfTopics += Section.Topics.Num();
    }

    // Generate Nodes for Topics and Subtopics
    int32 TopicIndex = 0;
    for (const FSectionStruct& Section : GameInstanceSectionDataArray)
    {
        for (const FTopic& Topic : Section.Topics)
        {
            // Create a node for the Topic
            ANodeActorBase* TopicNode = CreateNode(Topic.Title, CalculateTopicPosition(TopicIndex, TotalNumberOfTopics) + StartPosition);
            NodeActors.Add(TopicNode);
            TopicIndex++;

            // Create a node for each Subtopic
            int32 SubtopicIndex = 0;
            for (const FSubtopic& Subtopic : Topic.Subtopics)
            {
                ANodeActorBase* SubtopicNode = CreateNode(Subtopic.Title, CalculateSubTopicPosition(TopicIndex, SubtopicIndex, Topic.Subtopics.Num(), TotalNumberOfTopics));
                NodeActors.Add(SubtopicNode);

                CreateEdge(TopicNode, SubtopicNode);

                SubtopicIndex++;
            }
        }
    }
}

ANodeActorBase* ANodeManager::CreateNode(const FString& NodeName, const FVector& Position)
{
    UWorld* World = GetWorld();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    if (NodeBlueprintClass)
    {
        ANodeActorBase* NodeActor = World->SpawnActor<ANodeActorBase>(NodeBlueprintClass, Position, FRotator::ZeroRotator, SpawnParams);
        if (NodeActor)
        {
            NodeActor->SetNodeText(NodeName);
            return NodeActor;
        }
    }

    return nullptr;
}


//FVector ANodeManager::CalculateTopicPosition(int32 TopicIndex)
//{
//    StartPosition = FVector(-2230.000000, -360.000000, 0);
//    // Suppose Topics are arranged vertically with 100 unit spacing
//    return FVector(0.f, TopicIndex * 500.f, 0.f) + StartPosition;
//}
//
//FVector ANodeManager::CalculateSubTopicPosition(int32 TopicIndex, int32 SubTopicIndex)
//{
//    
//    // Suppose Subtopics are arranged horizontally with 100 unit spacing, relative to their parent Topic
//    FVector TopicPosition = CalculateTopicPosition(TopicIndex);
//    return FVector(TopicPosition.X + (SubTopicIndex + 1) * 100.f, TopicPosition.Y, TopicPosition.Z);
//}


FVector ANodeManager::CalculateTopicPosition(int32 TopicIndex, int32 TotalNumberOfTopics)
{
    // Implement this function to calculate where the Topic nodes should be positioned
    // Example:
    float Radius = 1000.0f;
    float AngleStep = 360.0f / TotalNumberOfTopics;
    float CurrentAngle = AngleStep * TopicIndex;
    FVector Position;
    Position.X = Radius * FMath::Cos(FMath::DegreesToRadians(CurrentAngle));
    Position.Y = Radius * FMath::Sin(FMath::DegreesToRadians(CurrentAngle));
    Position.Z = 0;

    return Position;
}

FVector ANodeManager::CalculateSubTopicPosition(int32 TopicIndex, int32 SubTopicIndex, int32 TotalNumberOfSubTopics, int32 TotalNumberOfTopics)
{
    // Implement this function to calculate where the Subtopic nodes should be positioned relative to their Topic
    // Example:
    float Radius = 300.0f; // Subtopics will be closer to their Topic
    float AngleStep = 360.0f / TotalNumberOfSubTopics;
    float CurrentAngle = AngleStep * SubTopicIndex;
    FVector Position;
    Position.X = Radius * FMath::Cos(FMath::DegreesToRadians(CurrentAngle));
    Position.Y = Radius * FMath::Sin(FMath::DegreesToRadians(CurrentAngle));
    Position.Z = 0;

    FVector TopicPosition = CalculateTopicPosition(TopicIndex, TotalNumberOfTopics);

    // Add the position of the parent Topic to the calculated position
    return Position + TopicPosition;
}


void ANodeManager::CreateEdge(ANodeActorBase* Node1, ANodeActorBase* Node2)
{
    // Ensure the world exists
    UWorld* World = GetWorld();
    if (!World) return;

    // Ensure the Edge blueprint class is set
    if (!EdgeBlueprintClass) return;

    // Spawn params
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    // Create edge between Node1 and Node2
    AEdgeActorBase* EdgeActor = World->SpawnActor<AEdgeActorBase>(EdgeBlueprintClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    if (EdgeActor)
    {
        EdgeActor->SetNodes(Node1, Node2);
        EdgeActors.Add(EdgeActor);
    }
}

