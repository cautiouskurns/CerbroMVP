// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "Engine/DataAsset.h"

#include "CoreDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UCoreDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FSectionStruct> Sections;
	
};
