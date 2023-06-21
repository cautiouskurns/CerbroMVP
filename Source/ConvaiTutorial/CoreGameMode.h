// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

public:

	UPROPERTY(EditAnywhere, Category = "Manager")
	TSubclassOf<class ANodeManager> NodeManagerClass;
	
private:
	UPROPERTY()
	class ANodeManager* NodeManager;

};

