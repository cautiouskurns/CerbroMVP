// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "UObject/NoExportTypes.h"

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
