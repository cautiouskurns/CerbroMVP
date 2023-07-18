// Fill out your copyright notice in the Description page of Project Settings.


#include "EdgeActorBase.h"

#include "NodeActorBase.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEdgeActorBase::AEdgeActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//EdgeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeMesh"));
	//RootComponent = EdgeMesh;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Create the StaticMeshComponent and attach it to the Root
	EdgeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeMesh"));
	EdgeMesh->SetupAttachment(RootComponent);

}

void AEdgeActorBase::SetNodes(ANodeActorBase* StartNode, ANodeActorBase* EndNode)
{
	if (StartNode && EndNode && EdgeMesh)
	{
		float Radius = GetStaticMeshComponentRadius(StartNode->NodeMesh);

		NodeOffsetStart = FVector(0, 0, Radius);
		NodeOffsetEnd = FVector(0, 0, Radius * 0.5);

		FVector StartPos = StartNode->NodeMesh->GetComponentLocation() + NodeOffsetStart;
		FVector EndPos = EndNode->NodeMesh->GetComponentLocation() + NodeOffsetEnd;

		// Position
		FVector MidPoint = (StartPos + EndPos) / 2;
		SetActorLocation(StartPos);
		//SetActorLocation(MidPoint);

		// Rotation
		FVector Direction = (EndPos - StartPos).GetSafeNormal();
		FRotator Rotation = Direction.Rotation();
		SetActorRotation(Rotation);

		// Scale
		float Distance = FVector::Dist(StartPos, EndPos);
		float ScalingFactor = 0.01f; // adjust this value as needed
		FVector Scale = FVector(0.05, 0.05, Distance * ScalingFactor);  // adjust the 1s as needed for your edge's width and height
		EdgeMesh->SetWorldScale3D(Scale);
	}
}

void AEdgeActorBase::SetStartEndNodes(const FVector& StartPos, const FVector& EndPos)
{
	if (EdgeMesh)
	{
		// Position
		FVector MidPoint = (StartPos + EndPos) / 2;
		SetActorLocation(MidPoint);

		// Rotation
		FVector Direction = (EndPos - StartPos).GetSafeNormal();
		FRotator Rotation = Direction.Rotation();
		SetActorRotation(Rotation);

		// Scale
		float Distance = FVector::Dist(StartPos, EndPos);
		float ScalingFactor = 0.01f; // adjust this value as needed
		FVector Scale = FVector(0.05, 0.05, Distance * ScalingFactor);  // adjust the 1s as needed for your edge's width and height
		EdgeMesh->SetWorldScale3D(Scale);
	}
}


float AEdgeActorBase::GetStaticMeshComponentRadius(UStaticMeshComponent* StaticMeshComponent)
{
	if (StaticMeshComponent == nullptr)
	{
		// Handle the case where the StaticMeshComponent is invalid.
		return 0.0f;
	}

	UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();
	if (StaticMesh == nullptr)
	{
		// Handle the case where the StaticMesh is invalid.
		return 0.0f;
	}

	FVector BoundsExtent = StaticMesh->GetBounds().BoxExtent;
	float MaxExtent = FMath::Max3(BoundsExtent.X, BoundsExtent.Y, BoundsExtent.Z);

	return MaxExtent;
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

}

