
// This class is responsible for creating, managing, and positioning nodes and edges.


#include "NodeManager.h"
#include "GraphManagement/NodeActorBase.h"
#include "ReadWriteJsonFile.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "BaseGameInstance.h"
#include "NodeDataLoader.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ANodeManager::ANodeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // The start position is set to (0, 0, 100) in the 3D space.
    StartPosition = FVector(0, 0, 100);

    NodeDataLoader = NewObject<UNodeDataLoader>();

    if (NodeDataLoader)
    {
        UWorld* World = GetWorld();
        NodeDataLoader->SetWorld(World);
    }
}

// This function is called when the game starts or when the actor is spawned.
// It sets a timer to call InitializeNodesByTopic function at the start of next tick.
void ANodeManager::BeginPlay()
{
	Super::BeginPlay();

    SubjectSwitch("Law");
}

// Called every frame
void ANodeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// This function initializes the nodes by retrieving data from the GameInstance.
void ANodeManager::InitializeNodes()
{
    UWorld* World = GetWorld();
    if (!World) return;

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GameInstance) return;

    TArray<FSectionStruct> GameInstanceSectionDataArray = GameInstance->SectionDataArray;
    TArray<FSubtopic> GameInstanceSubTopicDataArray = GameInstance->SubTopicStructArray;


    // Create nodes based on the topics and subtopics in the GameInstance.

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
    }


    // Create a node for each subtopic
    for (int i = 0; i < TotalSubTopics; ++i)  
    {
        FActorSpawnParameters SpawnParams;

        if (NodeBlueprintClass)
        {
            // Spawn a node actor
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


// This function positions the nodes in a grid.
void ANodeManager::PositionNodes()
{
    // For each node, calculate its position based on its index and place it in the world.
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
    SetGraphNodeText();
}


// This function sets the text for each node in the graph.
void ANodeManager::SetGraphNodeText()
{
    // Geenrate subtopic names and contents
    TArray<FString> SubTopicNames = NodeDataLoader->GenerateSubtopicNames();
    TArray<FString> SubTopicContents = NodeDataLoader->GenerateSubtopicContents(CurrentSubject);

    for (int32 i = 0; i < NodeActors.Num(); i++)
    {
        AActor* NodeActor = NodeActors[i];
        if (!NodeActor) continue;  // skip if the pointer is null

        ANodeActorBase* NodeActorBase = Cast<ANodeActorBase>(NodeActor);
        if (NodeActorBase && i < SubTopicNames.Num() && i < SubTopicContents.Num())
        {

            // Set the node's text to the corresponding subtopic name
            // Set the node's content to the corresponding subtopic content
            NodeActorBase->SetNodeTextAndContent(SubTopicNames[i], SubTopicContents[i]);

        }
    }
}

// This function generates edges between nodes.
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


// This function is called when the subject is switched.
void ANodeManager::SubjectSwitch(const FString& NewSubjectName)
{
    UWorld* World = GetWorld();
    if (!World) return;

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GameInstance) return;

    TArray<FSubjectStruct> GameInstanceSubjectDataArray = GameInstance->SubjectDataArray;

    // Find the new subject
    for (const FSubjectStruct& Subject : GameInstanceSubjectDataArray)
    {
        if (Subject.SubjectName == NewSubjectName)
        {
            // Clear current nodes and edges
            for (ANodeActorBase* Node : NodeActors)
            {
                if (Node != nullptr)
                {
                    Node->Destroy();
                }
            }
            NodeActors.Empty();

            for (AEdgeActorBase* Edge : EdgeActors)
            {
                if (Edge != nullptr)
                {
                    Edge->Destroy();
                }
            }
            EdgeActors.Empty();

            // Set the current subject and initialize nodes and edges for new subject
            CurrentSubject = Subject;
            GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ANodeManager::InitializeNodesBySubject);

            return;
        }
    }
}


// This function initializes nodes and edges for the current subject.
void ANodeManager::InitializeNodesBySubject()
{
    UWorld* World = GetWorld();
    if (!World) return;

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GameInstance) return;

    TArray<FSubjectStruct> GameInstanceSubjectDataArray = GameInstance->SubjectDataArray;

    // Determine total number of topics across all sections
    int32 TotalNumberOfTopics = 0;

 
    for (const FSectionStruct& Section : CurrentSubject.SubjectDetailsArray)
    {
        TotalNumberOfTopics += Section.Topics.Num();
    }
 
    // Generate Nodes for Topics and Subtopics
    int32 TopicIndex = 0;

    for (const FSectionStruct& Section : CurrentSubject.SubjectDetailsArray)
    {
        for (const FTopic& Topic : Section.Topics)
        {
            // Create a node for the Topic
            ANodeActorBase* TopicNode = CreateNode(Topic.Title, "", CalculateTopicPosition(TopicIndex, TotalNumberOfTopics) + StartPosition, true);
            TopicNode->ParentTopic = nullptr;

            TopicNode->SetNodeTextFontColor(TopicFontColor);  // Set font color for topic
            NodeActors.Add(TopicNode);


            // Create a node for each Subtopic
            int32 SubtopicIndex = 0;
            for (const FSubtopic& Subtopic : Topic.Subtopics)
            {
                ANodeActorBase* SubtopicNode = CreateNode(Subtopic.Title, Subtopic.Content, CalculateSubTopicPosition(TopicIndex, SubtopicIndex, Topic.Subtopics.Num(), TotalNumberOfTopics) + StartPosition, false);
                SubtopicNode->ParentTopic = TopicNode;

                SubtopicNode->SetNodeTextFontColor(SubtopicFontColor);  // Set font color for subtopic

                NodeActors.Add(SubtopicNode);

                CreateEdge(TopicNode, SubtopicNode);
                //CreateEdgeToSurface(TopicNode, SubtopicNode);

                SubtopicIndex++;
            }

            TopicIndex++;
        }
    }
}


// Create a node
ANodeActorBase* ANodeManager::CreateNode(const FString& NodeName, const FString& NodeContent, const FVector& Position, bool IsTopicNode)
{
    float TopicFontSize = 28.0f;
    float SubtopicFontSize = 18.0f;

    float TopicNodeSize = 1.0f;
    float SubTopicNodeSize = 0.5f;


    UWorld* World = GetWorld();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    if (NodeBlueprintClass)
    {
        ANodeActorBase* NodeActor = World->SpawnActor<ANodeActorBase>(NodeBlueprintClass, Position, FRotator::ZeroRotator, SpawnParams);
        if (NodeActor)
        {
            // Set font size based on whether it's a topic node
            NodeActor->SetNodeTextFontSize(IsTopicNode ? TopicFontSize : SubtopicFontSize);
            NodeActor->SetNodeText(NodeName);
            NodeActor->SetNodeSize(IsTopicNode ? TopicNodeSize : SubTopicNodeSize);
            NodeActor->SubtopicContent = NodeContent; // Set the subtopic content
            NodeActor->SubtopicTitle = NodeName; // Set the subtopic content

            // Set the material based on whether this is a Topic or Subtopic node
            UMaterialInterface* Material = IsTopicNode ? TopicNodeMaterial : SubtopicNodeMaterial;
            UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NodeActor);
            NodeActor->GetStaticMeshComponent()->SetMaterial(0, DynamicMaterial);
            return NodeActor;
        }
    }

    return nullptr;
}


// Calculate the position of the Topic node based on its index and the total number of topics
FVector ANodeManager::CalculateTopicPosition(int32 TopicIndex, int32 TotalNumberOfTopics)
{
    // Implement this function to calculate where the Topic nodes should be positioned
    // Example:
    float Radius = 500.0f;
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


// Create directed edge between Node1 and Node2
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


// Check if Node is a subtopic of TopicNode
bool ANodeManager::IsSubtopicOf(ANodeActorBase* Node, ANodeActorBase* TopicNode)
{
    return Node->ParentTopic == TopicNode;
}


// Highlight the selected topic and its subtopics
void ANodeManager::HighlightTopic(ANodeActorBase* TopicNode)
{
    // If the selected node is already highlighted, unhighlight it and its subtopics, 
    // and restore all other nodes to full opacity
    if (TopicNode->bIsHighlighted)
    {
        for (ANodeActorBase* Node : NodeActors)
        {
            Node->RestoreNodeOpacity();
        }

        TopicNode->bIsHighlighted = false;
    }
    else
    {
        for (ANodeActorBase* Node : NodeActors)
        {
            if (Node == TopicNode || IsSubtopicOf(Node, TopicNode))
            {
                Node->HighlightNode();
            }
            else
            {
                Node->LowerNodeOpacity();
            }
        }

        TopicNode->bIsHighlighted = true;
    }
}




