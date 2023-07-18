// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "ConvaiTutorial/BaseClasses/BaseGameInstance.h"

#include "ConvaiTutorial/Widgets/FolderWidget.h"

#include "Json.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonUtilities.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/GameEngine.h>

// Read a JSON file and return a FJsonStruct object.
FJsonStruct UReadWriteJsonFile::ReadStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
    JsonFilePath = FPaths::ProjectContentDir() + "TopicTestData2.json";
    bOutSuccess = true;

    // Reads a JSON file and attempts to deserialize it into a FJsonStruct object.
    TSharedPtr<FJsonObject> JsonObject = ReadJsonFileToJsonObject(JsonFilePath, bOutSuccess, OutInfoMessage);
    if (!bOutSuccess)
    {
        OutInfoMessage = FString::Printf(TEXT("JSON file not read successfully"));

        // Deserialize the JSON data into a FJsonStruct object.
        return FJsonStruct();
    }

    // Convert a JsonObject into a FJsonStruct instance.
    // If we failed to serialize the JSON data, then we return an empty FJsonStruct object.
    FJsonStruct StructToReturn;
    if (!FJsonObjectConverter::JsonObjectToUStruct<FJsonStruct>(JsonObject.ToSharedRef(), &StructToReturn, 0, 0))
    {
        bOutSuccess = false;
        OutInfoMessage = FString::Printf(TEXT("Failed to convert JSON object to struct"));
        return FJsonStruct();
    }

    bOutSuccess = true;
    OutInfoMessage = FString::Printf(TEXT("Convert JSON object to struct"));
    return StructToReturn;

}

FSectionStruct UReadWriteJsonFile::ReadNestedStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
    JsonFilePath = FPaths::ProjectContentDir() + "JSONStructTestSecton.json";
    bOutSuccess = true;



    // Reads a JSON file and attempts to deserialize it into a FJsonStruct object.
    TSharedPtr<FJsonObject> JsonObject = ReadJsonFileToJsonObject(JsonFilePath, bOutSuccess, OutInfoMessage);
    if (!bOutSuccess)
    {
        OutInfoMessage = FString::Printf(TEXT("JSON file not read successfully"));

        // Deserialize the JSON data into a FJsonStruct object.
        return FSectionStruct();
    }

    // Convert a JsonObject into a FJsonStruct instance.
    // If we failed to serialize the JSON data, then we return an empty FJsonStruct object.
    FSectionStruct StructToReturn;
    if (!FJsonObjectConverter::JsonObjectToUStruct<FSectionStruct>(JsonObject.ToSharedRef(), &StructToReturn, 0, 0))
    {
        bOutSuccess = false;
        OutInfoMessage = FString::Printf(TEXT("Failed to convert JSON object to struct"));
        return FSectionStruct();
    }
   

    bOutSuccess = true;
    OutInfoMessage = FString::Printf(TEXT("Convert JSON object to struct"));
    return StructToReturn;
}

// Read a JSON file and convert it into a FJsonObject
TSharedPtr<FJsonObject> UReadWriteJsonFile::ReadJsonFileToJsonObject(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{

    FString JsonString; // Our result string to hold Json string data

    // Load the raw JSON string from the file
    if (!FFileHelper::LoadFileToString(JsonString, *JsonFilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load file: %s"), *JsonFilePath);
        return nullptr;
    }

    // Create a pointer to hold the json serialized data
    TSharedPtr<FJsonObject> JsonObject;

    // Parse the raw JSON string in JsonString into JsonObject.
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), JsonObject))
    {
        bOutSuccess = false;
        OutInfoMessage = FString::Printf(TEXT("Failed to parse JSON file: '%s'"), *JsonString);
        return nullptr;
    }

    return JsonObject;
}

// Write a FJsonObject to a data table.
void UReadWriteJsonFile::PopulateDataTable(UDataTable* DataTable, const FSectionStruct& Data, FString& OutInfoMessage)
{
    // Create a new row in the DataTable.
    FSectionStruct* DataRow = DataTable->FindRow<FSectionStruct>(FName(*Data.SectionName), TEXT("ContextString"), true);



    // If the row doesn't exist, create it.
    if (!DataRow)
    {
        DataTable->AddRow(FName(*Data.SectionName), Data);
        OutInfoMessage = FString::Printf(TEXT("Row didn't exist. Added"));

    }
    else // if the row already exists, modify it.
    {
        *DataRow = Data;
        OutInfoMessage = FString::Printf(TEXT("Row already exists. Modify"));
    }
}


// Write a FJsonStruct object to a JSON file.
void UReadWriteJsonFile::WriteStructToJsonObject(FString JsonFilePath, FJsonStruct StructToWrite, bool& bOutSuccess, FString& OutInfoMessage)
{
    // Convert the FJsonStruct object to a FJsonObject.
    TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(StructToWrite);
    if (JsonObject == nullptr)
    {
        bOutSuccess = false;
        OutInfoMessage = FString::Printf(TEXT("Failed to convert struct to JSON object"));
        return;
    }

    WriteJson(JsonFilePath, JsonObject, bOutSuccess, OutInfoMessage);
}

// Write a FJsonNestedStruct object to a JSON file.
void UReadWriteJsonFile::WriteNestedStructToJsonObject(FString JsonFilePath, FSectionStruct StructToWrite, bool& bOutSuccess, FString& OutInfoMessage)
{
    // Convert the FJsonStruct object to a FJsonObject.
    TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(StructToWrite);
    if (JsonObject == nullptr)
    {
        bOutSuccess = false;
        OutInfoMessage = FString::Printf(TEXT("Failed to convert struct to JSON object"));
        return;
    }

    WriteJson(JsonFilePath, JsonObject, bOutSuccess, OutInfoMessage);
}

// Write JSON files
void UReadWriteJsonFile::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage)
{
    FString OutputString;
    /* JsonFilePath = FPaths::ProjectContentDir() + "TopicTestData2.json";*/
    JsonFilePath = FPaths::ProjectContentDir() + "EmployeeData2.json";

    //Convert Json object to string
    if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&OutputString)))
    {
        bOutSuccess = false;
        OutInfoMessage = FString::Printf(TEXT("Failed to serialize JSON object: '%s'"), *JsonFilePath);
        return;
    }

    //Write string to file
    if (!FFileHelper::SaveStringToFile(OutputString, *JsonFilePath))
    {
        return;
    }
    bOutSuccess = true;
    OutInfoMessage = FString::Printf(TEXT("Write Json succeesed: '%s'"), *JsonFilePath);

}
