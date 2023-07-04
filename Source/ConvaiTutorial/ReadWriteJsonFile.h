// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Misc/Paths.h"

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

USTRUCT(BlueprintType)
struct FTest
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Question;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Answers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CorrectAnswer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int TimesTested;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int TimesCorrect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ProficiencyScore;
};



USTRUCT(BlueprintType)
struct FSubtopic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Content;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FTest> Questions;
};


USTRUCT(BlueprintType)
struct FTopic
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSubtopic> Subtopics;
};

USTRUCT(BlueprintType)
struct FSectionStruct : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SectionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FTopic> Topics;
};


USTRUCT(BlueprintType)
struct FTreeViewItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> ChildrenIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ParentID;
};


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
