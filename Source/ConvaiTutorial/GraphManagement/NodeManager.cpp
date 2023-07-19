
// This class is responsible for creating, managing, and positioning nodes and edges.


#include "NodeManager.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "ConvaiTutorial/GraphManagement/NodeActorBase.h"
#include "ConvaiTutorial/GraphManagement/NodeDataLoader.h"

#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
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



// This function positions the nodes in a grid.
//void ANodeManager::PositionNodes()
//{
//    // For each node, calculate its position based on its index and place it in the world.
//    int32 size = FMath::RoundToInt(FMath::Sqrt(static_cast<float>(NodeActors.Num())));  // the number of nodes along one edge of the grid
//    float spacing = 1000.f / size;  // the distance between each node
//
//    for (int32 i = 0; i < NodeActors.Num(); i++)
//    {
//        AActor* NodeActor = NodeActors[i];
//        if (!NodeActor) continue;  // skip if the pointer is null
//
//        FVector Position;
//
//        // Print position
//        Position.X = (i % size) * spacing;
//        Position.Y = (i / size) * spacing;
//        Position.Z = 0;
//
//        NodeActor->SetActorLocation(Position + StartPosition);
//       
//    }
//
//    // Set Node Text
//    SetGraphNodeText();
//}
//
//
//// This function sets the text for each node in the graph.
//void ANodeManager::SetGraphNodeText()
//{
//    // Geenrate subtopic names and contents
//    TArray<FString> SubTopicNames = NodeDataLoader->GenerateSubtopicNames();
//    TArray<FString> SubTopicContents = NodeDataLoader->GenerateSubtopicContents(CurrentSubject);
//
//    for (int32 i = 0; i < NodeActors.Num(); i++)
//    {
//        AActor* NodeActor = NodeActors[i];
//        if (!NodeActor) continue;  // skip if the pointer is null
//
//        ANodeActorBase* NodeActorBase = Cast<ANodeActorBase>(NodeActor);
//        if (NodeActorBase && i < SubTopicNames.Num() && i < SubTopicContents.Num())
//        {
//
//            // Set the node's text to the corresponding subtopic name
//            // Set the node's content to the corresponding subtopic content
//            NodeActorBase->SetNodeTextAndContent(SubTopicNames[i], SubTopicContents[i]);
//
//        }
//    }
//}

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

    TArray<FFieldStruct> GameInstanceFieldDataArray = GameInstance->FieldDataArray;

    // Find the new subject
    for (const FFieldStruct& Field : GameInstanceFieldDataArray)
    {
        for (const FAreaStruct& Area : Field.Areas)
        {
            for (const FSubjectGroupStruct& SubjectGroup : Area.SubjectGroups)
            {
                for (const FSubjectStruct& Subject : SubjectGroup.Subjects)
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

    TArray<FFieldStruct> GameInstanceFieldDataArray = GameInstance->FieldDataArray;

    float BaseSectionRadius = 500.f;
    float BaseTopicRadius = 300.f;
    float BaseSubTopicRadius = 100.f;

    // Determine total number of sections
    int32 TotalNumberOfSections = CurrentSubject.SubjectDetailsArray.Num();
    int32 TotalNumberOfTopics = 0;
    int32 TotalNumberOfSubtopics = 0;

    // Generate Nodes for Sections, Topics and Subtopics
    int32 SectionIndex = 0;
    int32 TopicIndex = 0;

    for (const FSectionStruct& Section : CurrentSubject.SubjectDetailsArray)
    {
        TotalNumberOfTopics += Section.Topics.Num();
        for (const FTopic& Topic : Section.Topics)
        {
            TotalNumberOfSubtopics += Topic.Subtopics.Num();
        }
    }

    // Calculate radii based on the total number of sections, topics, and subtopics
    float SectionRadius = BaseSectionRadius * FMath::Sqrt(static_cast<float>(TotalNumberOfSections));
    float TopicRadius = BaseTopicRadius * FMath::Sqrt(static_cast<float>(TotalNumberOfTopics));
    float SubTopicRadius = BaseSubTopicRadius * FMath::Sqrt(static_cast<float>(TotalNumberOfSubtopics));




    for (const FSectionStruct& Section : CurrentSubject.SubjectDetailsArray)
    {
        // Create a node for the Section
        ANodeActorBase* SectionNode = CreateNode(Section.SectionName, "", CalculateNodePosition(SectionIndex, TotalNumberOfSections, StartPosition, SectionRadius), 0);
        SectionNode->ParentTopic = nullptr;

        SectionNode->SetNodeTextFontColor(SectionFontColor);  // Set font color for section
        NodeActors.Add(SectionNode);

        //int32 TotalNumberOfTopics = Section.Topics.Num();

        for (const FTopic& Topic : Section.Topics)
        {
            // Create a node for the Topic
            ANodeActorBase* TopicNode = CreateNode(Topic.Title, "", CalculateNodePosition(TopicIndex, TotalNumberOfTopics, SectionNode->GetActorLocation(), TopicRadius), 1);
            TopicNode->ParentTopic = SectionNode;  // Set the parent to the section node

            TopicNode->SetNodeTextFontColor(TopicFontColor);  // Set font color for topic
            NodeActors.Add(TopicNode);

            CreateEdge(SectionNode, TopicNode);

            // Create a node for each Subtopic
            int32 SubtopicIndex = 0;
            for (const FSubtopic& Subtopic : Topic.Subtopics)
            {
                ANodeActorBase* SubtopicNode = CreateNode(Subtopic.Title, Subtopic.Content, CalculateNodePosition(SubtopicIndex, Topic.Subtopics.Num(), TopicNode->GetActorLocation(), SubTopicRadius), 2);
                SubtopicNode->ParentTopic = TopicNode;

                SubtopicNode->SetNodeTextFontColor(SubtopicFontColor);  // Set font color for subtopic

                NodeActors.Add(SubtopicNode);

                CreateEdge(TopicNode, SubtopicNode);

                SubtopicIndex++;
            }

            TopicIndex++;
        }

        SectionIndex++;
    }
}


ANodeActorBase* ANodeManager::CreateNode(const FString& NodeName, const FString& NodeContent, const FVector& Position, int NodeType)
{
    float SectionFontSize = 32.0f;
    float TopicFontSize = 28.0f;
    float SubtopicFontSize = 18.0f;

    float SectionNodeSize = 1.5f;
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
            // Set font size based on NodeType
            if (NodeType == 0)
            {
                NodeActor->SetNodeTextFontSize(SectionFontSize);
                NodeActor->SetNodeSize(SectionNodeSize);

                // Move the NodeTextComponent up based on the size of the node
                FVector TextPosition(0.0f, 0.0f, SectionNodeSize * 100.0f);  // Adjust the multiplier based on your needs
                NodeActor->NodeTextComponent->SetRelativeLocation(TextPosition);
            }
            else if (NodeType == 1)
            {
                NodeActor->SetNodeTextFontSize(TopicFontSize);
                NodeActor->SetNodeSize(TopicNodeSize);

                // Move the NodeTextComponent up based on the size of the node
                FVector TextPosition(0.0f, 0.0f, TopicNodeSize * 100.0f);  // Adjust the multiplier based on your needs
                NodeActor->NodeTextComponent->SetRelativeLocation(TextPosition);
            }
            else if (NodeType == 2)
            {
                NodeActor->SetNodeTextFontSize(SubtopicFontSize);
                NodeActor->SetNodeSize(SubTopicNodeSize);

                // Move the NodeTextComponent up based on the size of the node
                FVector TextPosition(0.0f, 0.0f, SubTopicNodeSize * 100.0f);  // Adjust the multiplier based on your needs
                NodeActor->NodeTextComponent->SetRelativeLocation(TextPosition);
            }

            NodeActor->SetNodeText(NodeName);
            NodeActor->SubtopicContent = NodeContent; // Set the subtopic content
            NodeActor->SubtopicTitle = NodeName; // Set the subtopic content

            // Set the material based on NodeType
            UMaterialInterface* Material = nullptr; // Initialize Material to nullptr here
            if (NodeType == 0)
            {
                Material = SectionNodeMaterial;
            }
            else if (NodeType == 1)
            {
                Material = TopicNodeMaterial;
            }
            else if (NodeType == 2)
            {
                Material = SubtopicNodeMaterial;
            }

            if (Material)  // Only use Material if it is not nullptr
            {
                UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NodeActor);
                NodeActor->GetStaticMeshComponent()->SetMaterial(0, DynamicMaterial);
            }

            return NodeActor;
        }
    }

    return nullptr;
}


//float ANodeManager::GetNodeSizeBasedOnType(ENodeType NodeType)
//{
//    switch (NodeType)
//    {
//    case ENodeType::Section:
//        return SectionNodeSize;
//    case ENodeType::Topic:
//        return TopicNodeSize;
//    case ENodeType::Subtopic:
//        return SubTopicNodeSize;
//    default:
//        return 1.0f;  // Default size
//    }
//}


FVector ANodeManager::CalculateNodePosition(int32 NodeIndex, int32 TotalNumberOfNodes, FVector ParentNodePosition, float Radius)
{
    // Implement this function to calculate where the nodes should be positioned
    // Example:
    float AngleStep = 360.0f / TotalNumberOfNodes;
    float CurrentAngle = AngleStep * NodeIndex;
    FVector Position;
    Position.X = Radius * FMath::Cos(FMath::DegreesToRadians(CurrentAngle));
    Position.Y = Radius * FMath::Sin(FMath::DegreesToRadians(CurrentAngle));
    Position.Z = 0;

    // Add the position of the parent Node to the calculated position
    return Position + ParentNodePosition;
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


void ANodeManager::HighlightNode(ANodeActorBase* NodeToHighlight)
{
    // If the selected node is already highlighted, unhighlight it and its children, 
    // and restore all other nodes to full opacity
    if (NodeToHighlight->bIsHighlighted)
    {
        for (ANodeActorBase* Node : NodeActors)
        {
            Node->RestoreNodeOpacity();
        }

        NodeToHighlight->bIsHighlighted = false;
    }
    else
    {
        for (ANodeActorBase* Node : NodeActors)
        {
            if (Node == NodeToHighlight || IsChildOf(Node, NodeToHighlight) || IsParentOf(NodeToHighlight, Node))
            {
                Node->HighlightNode();
            }
            else
            {
                Node->LowerNodeOpacity();
            }
        }

        NodeToHighlight->bIsHighlighted = true;
    }
}


bool ANodeManager::IsChildOf(ANodeActorBase* PotentialChild, ANodeActorBase* PotentialParent)
{
    // If the PotentialChild is a direct child of the PotentialParent
    if (PotentialChild->ParentTopic == PotentialParent || PotentialChild->ParentSection == PotentialParent)
    {
        return true;
    }
    // If the PotentialChild is not at the top of the hierarchy, check its parent
    else if (PotentialChild->ParentTopic != nullptr)
    {
        return IsChildOf(PotentialChild->ParentTopic, PotentialParent);
    }
    else if (PotentialChild->ParentSection != nullptr)
    {
        return IsChildOf(PotentialChild->ParentSection, PotentialParent);
    }

    // If we've reached here, the PotentialChild is not a child of the PotentialParent
    return false;
}

bool ANodeManager::IsParentOf(ANodeActorBase* PotentialParent, ANodeActorBase* PotentialChild)
{
    if (PotentialChild->ParentTopic == PotentialParent)
    {
        return true;
    }
    else if (PotentialChild->ParentSection == PotentialParent)
    {
        return true;
    }
    else if (PotentialChild->ParentTopic && PotentialChild->ParentTopic->ParentSection == PotentialParent)
    {
        return true;
    }

    return false;
}

