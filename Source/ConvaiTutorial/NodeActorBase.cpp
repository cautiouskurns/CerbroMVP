// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeActorBase.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANodeActorBase::ANodeActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Create the StaticMeshComponent and attach it to the Root
	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
	NodeMesh->SetupAttachment(RootComponent);

	NodeTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NodeText"));
	NodeTextComponent->SetupAttachment(RootComponent); // attach to the root component

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

void ANodeActorBase::SetNodeText(const FString& NewText)
{
	if (NodeTextComponent)
	{
		NodeTextComponent->SetText(FText::FromString(NewText));
	}
}

