// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "Misc/DateTime.h"
#include "Json.h"

#include "MyHttpClient.generated.h"

UCLASS()
class CONVAITUTORIAL_API AMyHttpClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyHttpClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // void SendRequest(FString Url, FString Verb, FString Content, FString ContentType);
	void SendLinRegRequest(FString Url, FString Verb, TArray<FVector2D> Points);

    // void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnLinRegResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);


    // UFUNCTION(BlueprintCallable, Category = "My Category")
	// FString GenerateLineChartData();

	// UFUNCTION(BlueprintCallable, Category = "My Category")
	// void UpdateChartData();

	TArray<TSharedPtr<FJsonValue>> Timestamps;
    TArray<TSharedPtr<FJsonValue>> Values;

};
