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

	// Create the TextRenderComponent and attach it to the Root (we don't want it to move around with the camera)
	NodeTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NodeText"));
	NodeTextComponent->SetupAttachment(RootComponent); // attach to the root component
	NodeTextComponent->SetWorldSize(1000.0f); // sets the size of the text in the world

	// Set the default font
	bIsHighlighted = false;
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


// Set NodeTextComponent text to NewText for this node
void ANodeActorBase::SetNodeText(const FString& NewText)
{
	if (NodeTextComponent)
	{
		NodeTextComponent->SetText(FText::FromString(NewText));
	}
}

// Set the node text and content
void ANodeActorBase::SetNodeTextAndContent(const FString& Text, const FString& Content)
{
	SetNodeText(Text);
	SubtopicContent = Content;
}


// Set the font size of the node
void ANodeActorBase::SetNodeTextFontSize(float FontSize)
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


// Set the font of the node text
void ANodeActorBase::SetNodeTextFontColor(FColor Color)
{
	if (NodeTextComponent)
	{
		NodeTextComponent->SetTextRenderColor(Color);
	}
}



// Set the size of the node
void ANodeActorBase::SetNodeSize(float NodeSize)
{
	// Assuming the sphere's scale is 1:1:1, you can simply adjust the scale based on the radius
	NodeMesh->SetWorldScale3D(FVector(NodeSize));

	// Adjust the position of the node to keep its center at the same height
	float OriginalScale = 1.0f; // replace this with the actual original scale if it's not 1
	float DeltaHeight = 0.5f * (OriginalScale - NodeSize);
	FVector Pos = GetActorLocation();
	Pos.Z += 100 * DeltaHeight;
	SetActorLocation(Pos);
}



// Set the material of the node
void ANodeActorBase::SetNodeMaterial(UMaterialInterface* Material)
{
	UStaticMeshComponent* MeshComponent = GetStaticMeshComponent();
	if (MeshComponent)
	{
		MeshComponent->SetMaterial(0, Material);
	}
}


// Get the StaticMeshComponent of the node
UStaticMeshComponent* ANodeActorBase::GetStaticMeshComponent() const
{
	return FindComponentByClass<UStaticMeshComponent>();
}


// Set the emissive color of the node to make it glow or stand out
void ANodeActorBase::HighlightNode()
{

	if (NodeMesh)
	{
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(GetStaticMeshComponent()->GetMaterial(0));
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(FName("EmissiveColor"), FLinearColor::White);
		}
	}

}


// Set opacity of the node to make it transparent
void ANodeActorBase::RestoreNodeOpacity()
{
	if (NodeMesh)
	{
		UMaterialInstanceDynamic* Material = NodeMesh->CreateDynamicMaterialInstance(0);
		if (Material)
		{
			Material->SetScalarParameterValue(FName("Opacity"), 1.0f);  // restore to full opacity
		}
	}

	bIsHighlighted = false;
}


// Set opacity of the node to make it transparent
void ANodeActorBase::LowerNodeOpacity()
{
	if (NodeMesh)
	{
		UMaterialInstanceDynamic* Material = NodeMesh->CreateDynamicMaterialInstance(0);
		if (Material)
		{
			Material->SetScalarParameterValue(FName("Opacity"), 0.05f);  // lower opacity
		}
	}

	bIsHighlighted = false;
}