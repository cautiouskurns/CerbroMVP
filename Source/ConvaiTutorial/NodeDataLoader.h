// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReadWriteJsonFile.h"
#include "BaseGameInstance.h"
#include "NodeDataLoader.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UNodeDataLoader : public UObject
{
	GENERATED_BODY()
	
protected:
	UWorld* World;

public:
	void SetWorld(UWorld* InWorld);

	TArray<FString> GenerateSubtopicNames();

	TArray<FString> GenerateSubtopicContents(const FSubjectStruct& CurrentSubject);


};
