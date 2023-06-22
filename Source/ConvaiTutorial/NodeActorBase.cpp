// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeActorBase.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/Font.h"
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
	NodeTextComponent->SetWorldSize(1000.0f); // sets the size of the text in the world

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

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && NodeTextComponent)
	{
		FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
		FVector Direction = PlayerLocation - GetActorLocation();
		FRotator NewRotation = Direction.Rotation();
		NodeTextComponent->SetWorldRotation(NewRotation);
	}

}

void ANodeActorBase::SetNodeText(const FString& NewText)
{
	if (NodeTextComponent)
	{
		NodeTextComponent->SetText(FText::FromString(NewText));
	}
}

void ANodeActorBase::SetFontSize(float FontSize)
{
	if (NodeTextComponent)
	{
		if (NodeFont)
		{
			NodeTextComponent->SetWorldSize(FontSize);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NodeFont is nullptr."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NodeTextComponent is nullptr."));
	}
}

void ANodeActorBase::SetFontColor(FColor Color)
{
	if (NodeTextComponent)
	{
		NodeTextComponent->SetTextRenderColor(Color);
	}
}


void ANodeActorBase::SetMaterial(UMaterialInterface* Material)
{
	UStaticMeshComponent* MeshComponent = GetStaticMeshComponent();
	if (MeshComponent)
	{
		MeshComponent->SetMaterial(0, Material);
	}
}

UStaticMeshComponent* ANodeActorBase::GetStaticMeshComponent() const
{
	return FindComponentByClass<UStaticMeshComponent>();
}