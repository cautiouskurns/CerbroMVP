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


 // Assuming MyHttpClient is an instance of AMyHttpClient
    int NumPoints = 100;
	float Slope = 2.0f;
	float Intercept = 1.0f;
	float NoiseStdDev = 0.1f;
	TArray<FVector2D> Points = GenerateTestData(NumPoints, Slope, Intercept, NoiseStdDev);
	
    HttpClient->SendLinRegRequest("http://localhost:5000/predict", "POST", Points);

}


TArray<FVector2D> ACoreGameMode::GenerateTestData(int NumPoints, float Slope, float Intercept, float NoiseStdDev)
{
    TArray<FVector2D> Points;
    FRandomStream RandStream;

    for (int i = 0; i < NumPoints; i++)
    {
        float X = RandStream.FRand();
        float Y = Slope * X + Intercept + RandStream.FRandRange(-NoiseStdDev, NoiseStdDev);
        Points.Add(FVector2D(X, Y));
    }

    return Points;
}