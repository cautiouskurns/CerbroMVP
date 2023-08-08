// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "ConvaiTutorial/MyHttpClient.h"

#include "ConvaiTutorial/MetricHandling/AssessmentMetricsCalculator.h"

#include "CoreGameMode.generated.h"

/**
 * 
 */

UCLASS()
class CONVAITUTORIAL_API ACoreGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ACoreGameMode();

	virtual void BeginPlay() override;

    TArray<FVector2D> GenerateTestData(int NumPoints, float Slope, float Intercept, float NoiseStdDev);

public:

	UPROPERTY(EditAnywhere, Category = "Manager")
	TSubclassOf<class ANodeManager> NodeManagerClass;
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Node Manager")
	ANodeManager* NodeManager;

	UPROPERTY(BlueprintReadWrite, Category = "Assessment")
	UAssessmentMetricsCalculator* AssessmentMetricsCalculator;

	UPROPERTY(BlueprintReadWrite, Category = "HTTP")
	AMyHttpClient* HttpClient;

};

