// Fill out your copyright notice in the Description page of Project Settings.


#include "DataLoader.h"

#include "ConvaiTutorial/DataManagement/CoreDataAsset.h"
#include "ConvaiTutorial/DataManagement/ReadWriteJsonFile.h"

#include "Engine/DataTable.h"


// Then you can use this function to load your DataTable
UDataTable* UDataLoader::LoadYourDataTable()
{
    // The path to your DataTable that you imported in the editor
    FString DataTablePath = TEXT("/Game/Data/DT_Section.DT_Section");
    UDataTable* YourDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *DataTablePath));

    if (!YourDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load DataTable"));
        return nullptr;
    }

    return YourDataTable;
}

// You can use this function to get the data from the DataTable
void UDataLoader::GetDataTableData(UDataTable* DataTable)
{
    if (DataTable)
    {
        // This creates an array of the row structs in your DataTable
        TArray<FSectionStruct*> RowStructs;
        DataTable->GetAllRows(TEXT("Your Context"), RowStructs);

        // You can now iterate over the row structs and access their data
        for (FSectionStruct* RowStruct : RowStructs)
        {
            UE_LOG(LogTemp, Warning, TEXT("Section Name: %s"), *RowStruct->SectionName);
            // And so on for the other data in your struct...
        }
    }
}

