// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeActorBase.h"
#include "EdgeActorBase.h"
#include "NodeManager.generated.h"


UCLASS()
class CONVAITUTORIAL_API ANodeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Populates NodeActors array with instances of NodeActorBase
	void InitializeNodes();

	void InitializeNodesByTopic();

	ANodeActorBase* CreateNode(const FString& NodeName, const FVector& Position, bool IsTopicNode);

	FVector CalculateTopicPosition(int32 TopicIndex, int32 TotalNumberOfTopics);

	FVector CalculateSubTopicPosition(int32 TopicIndex, int32 SubTopicIndex, int32 TotalNumberOfSubTopics, int32 TotalNumberOfTopics);

	void CreateEdge(ANodeActorBase* Node1, ANodeActorBase* Node2);

	// Positions NodeActors in a grid
	void PositionNodes();

	TArray<FString> GenerateSubtopicNames();

	void SetNodeText();

	UFUNCTION(BlueprintCallable, Category = "Edge")
	void GenerateEdges();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Spawning")
	TSubclassOf<class ANodeActorBase> NodeBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge")
	TSubclassOf<class AEdgeActorBase> EdgeBlueprintClass;

	UPROPERTY()
	TArray<ANodeActorBase*> NodeActors;

	UPROPERTY()
	TArray<AEdgeActorBase*> EdgeActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeManager")
	FVector StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Materials")
	UMaterialInterface* TopicNodeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Materials")
	UMaterialInterface* SubtopicNodeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Config")
	FColor TopicFontColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Config")
	FColor SubtopicFontColor;

};