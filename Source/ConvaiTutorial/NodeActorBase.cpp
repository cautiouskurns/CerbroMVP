// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeActorBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANodeActorBase::ANodeActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
	RootComponent = NodeMesh;

}

// Called when the game starts or when spawned
void ANodeActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANodeActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

