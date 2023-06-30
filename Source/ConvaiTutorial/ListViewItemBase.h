// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListViewItemBase.generated.h"

/**
 * 
 */
UCLASS()
class CONVAITUTORIAL_API UListViewItemBase : public UUserWidget
{
	GENERATED_BODY()
	
};


USTRUCT(BlueprintType)
struct FListViewItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;
};