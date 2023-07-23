// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvaiTutorial/DataManagement/UserInteractionDataManager.h"


#include "Kismet/BlueprintFunctionLibrary.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Misc/Paths.h"
#include "KnowledgeStructs.h"
#include "Misc/FileHelper.h"
#include "Engine/DataTable.h"   // Include this

#include "ReadWriteJsonFile.generated.h"

class FJsonObject;

USTRUCT(BlueprintType)
struct FJsonStruct
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString topics;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString concepts;
};

class FJsonObject;

UCLASS()
class CONVAITUTORIAL_API UReadWriteJsonFile : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
        static FJsonStruct ReadStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);

    UFUNCTION(BlueprintCallable)
        static void WriteStructToJsonObject(FString JsonFilePath, FJsonStruct StructToWrite, bool& bOutSuccess, FString& OutInfoMessage);

    UFUNCTION(BlueprintCallable)
       static FSectionStruct ReadNestedStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);

    UFUNCTION(BlueprintCallable)
        static void WriteNestedStructToJsonObject(FString JsonFilePath, FSectionStruct StructToWrite, bool& bOutSuccess, FString& OutInfoMessage);

    UFUNCTION(BlueprintCallable)
        static void PopulateDataTable(UDataTable* DataTable, const FSectionStruct& Data, FString& OutInfoMessage);

    // 

    static TSharedPtr<FJsonObject> ReadJsonFileToJsonObject(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);

    static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage);

};
