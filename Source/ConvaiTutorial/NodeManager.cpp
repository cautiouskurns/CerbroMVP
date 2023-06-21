// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeManager.h"
#include "NodeActorBase.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "BaseGameInstance.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ANodeManager::ANodeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StartPosition = FVector(-2230.000000, -360.000000, 0);

}

// Called when the game starts or when spawned
void ANodeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANodeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANodeManager::InitializeNodes()
{
    UWorld* World = GetWorld();
    if (!World) return;

    for (int i = 0; i < 10; ++i)  // Create 10 nodes
    {
        FActorSpawnParameters SpawnParams;

        if (NodeBlueprintClass)
        {
            //FVector NodeZero(-2230.000000, -360.000000, -20.000000);

            ANodeActorBase* NodeActor = World->SpawnActor<ANodeActorBase>(NodeBlueprintClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
            NodeActors.Add(NodeActor);

            UE_LOG(LogTemp, Warning, TEXT("Node spawned!"));
        }
        else
        {
			UE_LOG(LogTemp, Warning, TEXT("NodeBlueprintClass is null!"));
		}

    }
}

void ANodeManager::PositionNodes()
{
    int32 size = FMath::RoundToInt(FMath::Sqrt(static_cast<float>(NodeActors.Num())));  // the number of nodes along one edge of the grid
    float spacing = 1000.f / size;  // the distance between each node

    for (int32 i = 0; i < NodeActors.Num(); i++)
    {
        AActor* NodeActor = NodeActors[i];
        if (!NodeActor) continue;  // skip if the pointer is null

        FVector Position;

        // Print position
        Position.X = (i % size) * spacing;
        Position.Y = (i / size) * spacing;
        Position.Z = 0;

        NodeActor->SetActorLocation(Position + StartPosition);


        // Setting text
        ANodeActorBase* NodeActorBase = Cast<ANodeActorBase>(NodeActor);
        UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
        if (GameInstance)
        {
            TArray<FSectionStruct> GameInstanceSectionDataArray = GameInstance->SectionDataArray;
            // Now you can use GameInstanceSectionDataArray
            if (NodeActorBase && i < GameInstanceSectionDataArray.Num())
            {
                FString DebugMessage = FString::Printf(TEXT("NodeActorBase 111"));

                // print debug message to log
                UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugMessage);

                NodeActorBase->SetNodeText(GameInstanceSectionDataArray[i].SectionName);
            }
        }

       
    }
}


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