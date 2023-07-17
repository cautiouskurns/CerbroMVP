// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KnowledgeStructs.h"
#include "Engine/DataTable.h"
#include "BaseGameInstance.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FFieldStructSaveData> FieldDataArraySaveData;
};
