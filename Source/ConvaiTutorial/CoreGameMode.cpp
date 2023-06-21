// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameMode.h"
#include "NodeManager.h"


ACoreGameMode::ACoreGameMode()
{
	NodeManager = nullptr;
}

void ACoreGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Instantiate the Node Manager
	//NodeManager = GetWorld()->SpawnActor<ANodeManager>(ANodeManager::StaticClass());
	if (NodeManagerClass)
	{
		NodeManager = GetWorld()->SpawnActor<ANodeManager>(NodeManagerClass);
	}
	if (NodeManager)
	{
		NodeManager->InitializeNodes();
		NodeManager->PositionNodes();
		NodeManager->GenerateEdges();
		
	}
}