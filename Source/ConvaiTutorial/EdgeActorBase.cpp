// Fill out your copyright notice in the Description page of Project Settings.


#include "EdgeActorBase.h"
#include "NodeActorBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEdgeActorBase::AEdgeActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EdgeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeMesh"));
	RootComponent = EdgeMesh;

	//NodeA = nullptr;
	//NodeB = nullptr;

}

void AEdgeActorBase::SetNodes(ANodeActorBase* InNodeA, ANodeActorBase* InNodeB)
{
	NodeA = InNodeA;
	NodeB = InNodeB;
}

// Called when the game starts or when spawned
void AEdgeActorBase::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AEdgeActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NodeA && NodeB)
	{
		// Set the position, rotation, and scale of the edge based on the nodes' positions
	}
}

