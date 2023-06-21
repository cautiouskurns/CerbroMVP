// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeActorBase.h"
#include "EdgeActorBase.generated.h"

UCLASS()
class CONVAITUTORIAL_API AEdgeActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEdgeActorBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	ANodeActorBase* NodeA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	ANodeActorBase* NodeB;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Edge")
	UStaticMeshComponent* EdgeMesh;

	UFUNCTION(BlueprintCallable, Category = "Edge")
	void SetNodes(ANodeActorBase* StartNode, ANodeActorBase* EndNode);

	UFUNCTION(BlueprintCallable, Category = "Edge")
	float GetStaticMeshComponentRadius(UStaticMeshComponent* StaticMeshComponent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The root scene component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeManager")
	FVector NodeOffset;




};
