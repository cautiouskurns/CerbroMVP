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

// Create an instance of MyHTTPClient
    HttpClient = NewObject<AMyHttpClient>(this);

// Set up the request data
    // FString Url = "http://localhost:5000/process_data";
    // FString Verb = "POST";
    // FString ContentType = "application/json";
    // FString Body = "{\"key1\":\"value111\", \"key2\":\"value222\"}";

    // Send the request
	//HttpClient->SendRequest(Url, Verb, Body, ContentType);

	//HttpClient->GenerateLineChartData();

}