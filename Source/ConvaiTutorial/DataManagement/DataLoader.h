// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "DataLoader.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UDataLoader : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Data")
	static UDataTable* LoadYourDataTable();

	UFUNCTION(BlueprintCallable, Category = "Data")
	static void GetDataTableData(UDataTable* DataTable);
	
};
