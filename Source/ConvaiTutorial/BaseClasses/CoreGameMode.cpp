// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameMode.h"

#include "ConvaiTutorial/GraphManagement/NodeManager.h"
#include "ConvaiTutorial/MetricHandling/AssessmentMetricsCalculator.h"



ACoreGameMode::ACoreGameMode()
{
	NodeManager = nullptr;
	//AssessmentMetricsCalculator = nullptr;
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

	// Initialize the AssessmentMetricsCalculator
	AssessmentMetricsCalculator = NewObject<UAssessmentMetricsCalculator>(this, UAssessmentMetricsCalculator::StaticClass());

}