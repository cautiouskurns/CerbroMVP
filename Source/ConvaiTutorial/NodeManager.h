// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphManagement/NodeActorBase.h"
#include "BaseGameInstance.h"
#include "GraphManagement/EdgeActorBase.h"
#include "ReadWriteJsonFile.h"
#include "AssessmentMetricsCalculator.h"
#include "NodeDataLoader.h"
#include "NodeManager.generated.h"


UCLASS()
class CONVAITUTORIAL_API ANodeManager : public AActor
{
	GENERATED_BODY()

	// Constructor: Sets default values for this actor's properties
public:
	ANodeManager();

	// Radius values for topic and subtopic nodes
private:
	static const float TOPIC_RADIUS;
	static const float SUBTOPIC_RADIUS;

	// BeginPlay: Called when the game starts or when spawned
protected:
	virtual void BeginPlay() override;

	// Tick: Called every frame
public:
	virtual void Tick(float DeltaTime) override;

// Assessment metrics calculator: Used to calculate different metrics related to assessment
private:
	UAssessmentMetricsCalculator* AssessmentMetricsCalculator;

	// Node data loader: Used to load the data for nodes
private:
	UNodeDataLoader* NodeDataLoader;

	// Current subject: The subject that is currently selected or being used
protected: // or private:
	UPROPERTY()
	FSubjectStruct CurrentSubject;

	// NodeActors: Array to store all the nodes in the graph
public:
	UPROPERTY()
	TArray<ANodeActorBase*> NodeActors;

	// EdgeActors: Array to store all the edges in the graph
public:
	UPROPERTY()
	TArray<AEdgeActorBase*> EdgeActors;

	// NodeBlueprintClass: Blueprint class to be used for creating node instances
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	TSubclassOf<class ANodeActorBase> NodeBlueprintClass;

	// EdgeBlueprintClass: Blueprint class to be used for creating edge instances
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge")
	TSubclassOf<class AEdgeActorBase> EdgeBlueprintClass;

	// StartPosition: The starting position for the node graph
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeManager")
	FVector StartPosition;

	// TopicNodeMaterial: Material to be used for topic nodes
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Materials")
	UMaterialInterface* TopicNodeMaterial;

	// SubtopicNodeMaterial: Material to be used for subtopic nodes
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Materials")
	UMaterialInterface* SubtopicNodeMaterial;

	// TopicFontColor: Font color for the text on topic nodes
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Config")
	FColor TopicFontColor;

	// SubtopicFontColor: Font color for the text on subtopic nodes
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Config")
	FColor SubtopicFontColor;



	// InitializeNodes: Populates NodeActors array with instances of NodeActorBase
	void InitializeNodes();

	// InitializeNodesBySubject: Initializes nodes based on the current subject
	void InitializeNodesBySubject();

	// CreateNode: Creates a new node with the given parameters
	ANodeActorBase* CreateNode(const FString& NodeName, const FString& NodeContent, const FVector& Position, bool IsTopicNode);

	// CalculateTopicPosition: Calculates the position of a topic node based on its index and the total number of topics
	FVector CalculateTopicPosition(int32 TopicIndex, int32 TotalNumberOfTopics);

	// CalculateSubTopicPosition: Calculates the position of a subtopic node based on its indices and the total numbers of subtopics and topics
	FVector CalculateSubTopicPosition(int32 TopicIndex, int32 SubTopicIndex, int32 TotalNumberOfSubTopics, int32 TotalNumberOfTopics);

	// CreateEdge: Creates an edge between two nodes
	void CreateEdge(ANodeActorBase* Node1, ANodeActorBase* Node2);

	// IsSubtopicOf: Checks if one node is a subtopic of another
	bool IsSubtopicOf(ANodeActorBase* Node, ANodeActorBase* TopicNode);

	// PositionNodes: Positions NodeActors in a grid
	void PositionNodes();

	// SetGraphNodeText: Sets the text for each node
	void SetGraphNodeText();

	// GenerateEdges: Creates edges between related nodes
	void GenerateEdges();

	// HighlightTopic: Highlights a topic node and its related nodes and edges
public:
	UFUNCTION(BlueprintCallable, Category = "Interaction Logic")
	void HighlightTopic(ANodeActorBase* TopicNode);

	// SubjectSwitch: Changes the current subject
	UFUNCTION(BlueprintCallable, Category = "Interaction Logic")
	void SubjectSwitch(const FString& NewSubjectName);




//private:
//	UAssessmentMetricsCalculator* AssessmentMetricsCalculator;
//
//public:	
//	// Sets default values for this actor's properties
//	ANodeManager();
//
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Populates NodeActors array with instances of NodeActorBase
//	void InitializeNodes();
//
//	UFUNCTION(BlueprintCallable, Category = "Interaction Logic")
//	void SubjectSwitch(const FString& NewSubjectName);
//
//	void InitializeNodesBySubject();
//
//
//	ANodeActorBase* CreateNode(const FString& NodeName, const FString& NodeContent, const FVector& Position, bool IsTopicNode);
//
//	FVector CalculateTopicPosition(int32 TopicIndex, int32 TotalNumberOfTopics);
//
//	FVector CalculateSubTopicPosition(int32 TopicIndex, int32 SubTopicIndex, int32 TotalNumberOfSubTopics, int32 TotalNumberOfTopics);
//
//	void CreateEdge(ANodeActorBase* Node1, ANodeActorBase* Node2);
//
//	bool IsSubtopicOf(ANodeActorBase* Node, ANodeActorBase* TopicNode);
//
//	UFUNCTION(BlueprintCallable, Category = "Edge")
//	void HighlightTopic(ANodeActorBase* TopicNode);
//
//
//	// Positions NodeActors in a grid
//	void PositionNodes();
//
//
//	void SetGraphNodeText();
//
//
//	UFUNCTION(BlueprintCallable, Category = "Edge")
//	void GenerateEdges();
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
//	TSubclassOf<class ANodeActorBase> NodeBlueprintClass;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge")
//	TSubclassOf<class AEdgeActorBase> EdgeBlueprintClass;
//
//	UPROPERTY()
//	TArray<ANodeActorBase*> NodeActors;
//
//	UPROPERTY()
//	TArray<AEdgeActorBase*> EdgeActors;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeManager")
//	FVector StartPosition;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Materials")
//	UMaterialInterface* TopicNodeMaterial;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Materials")
//	UMaterialInterface* SubtopicNodeMaterial;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Config")
//	FColor TopicFontColor;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Config")
//	FColor SubtopicFontColor;
//
//
//	// Add a pointer to UNodeDataLoader
//	UNodeDataLoader* NodeDataLoader;
//
//protected: // or private:
//	UPROPERTY()
//	FSubjectStruct CurrentSubject;
//
//private:
//	static const float TOPIC_RADIUS;
//	static const float SUBTOPIC_RADIUS;

};
