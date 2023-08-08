// Fill out your copyright notice in the Description page of Project Settings.

#include "Http.h"
#include "Misc/DateTime.h"
#include "Json.h"

#include "MyHttpClient.h"

// Sets default values
AMyHttpClient::AMyHttpClient()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyHttpClient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyHttpClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void AMyHttpClient::SendRequest(FString Url, FString Verb, FString Content, FString ContentType)
// {
//     TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
//     HttpRequest->SetURL(Url);
//     HttpRequest->SetVerb(Verb);
//     HttpRequest->SetHeader(TEXT("User-Agent"), "MyClient/1.0");
//     HttpRequest->SetHeader(TEXT("Content-Type"), ContentType);
//     HttpRequest->SetContentAsString(Content);
//     HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMyHttpClient::OnResponseReceived);
//     HttpRequest->ProcessRequest();
// }

// void AMyHttpClient::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
// {
//     if(!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
//     {
//         // Handle error here
//         return;
//     }
    
//     // Log or do something with the response
//     UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());
// }

void AMyHttpClient::SendLinRegRequest(FString Url, FString Verb, TArray<FVector2D> Points)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(Url);
    HttpRequest->SetVerb(Verb);
    HttpRequest->SetHeader(TEXT("User-Agent"), "MyClient/1.0");
    HttpRequest->SetHeader(TEXT("Content-Type"), "application/json");

    // Convert the x-components of Points to a JSON array
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    TArray<TSharedPtr<FJsonValue>> JsonXValues;
    for (auto& Point : Points)
    {
        JsonXValues.Add(MakeShareable(new FJsonValueNumber(Point.X)));
    }
    JsonObject->SetArrayField("x", JsonXValues);

    FString Body;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Body);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    HttpRequest->SetContentAsString(Body);

    HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMyHttpClient::OnLinRegResponseReceived);
    HttpRequest->ProcessRequest();
}

void AMyHttpClient::OnLinRegResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        // Handle error here
        return;
    }

    // Parse the JSON response
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        TArray<TSharedPtr<FJsonValue>> JsonPredictions = JsonObject->GetArrayField("prediction");

        // Convert the JSON array to TArray<double>
        TArray<double> Predictions;
        for (auto& JsonValue : JsonPredictions)
        {
            Predictions.Add(JsonValue->AsNumber());
        }

        // Log or do something with the predictions
        for (auto& Prediction : Predictions)
        {
            UE_LOG(LogTemp, Warning, TEXT("Prediction: %f"), Prediction);
        }
    }
}

// void AMyHttpClient::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
// {
//     if(!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
//     {
//         // Handle error here
//         return;
//     }
    
//     // Log or do something with the response
//     UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());
// }

// FString AMyHttpClient::GenerateLineChartData()
// {
//     TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
//     // TArray<TSharedPtr<FJsonValue>> Timestamps;
//     // TArray<TSharedPtr<FJsonValue>> Values;

//     // Generate data for 10 points
//     for (int i = 0; i < 10; i++)
//     {
//         // Simulating timestamp in seconds
//         int64 Timestamp = FDateTime::Now().ToUnixTimestamp() + i * 60;
//         // Simulating value (e.g., player's score)
//         int32 Value = 100 * i;

//         Timestamps.Add(MakeShareable(new FJsonValueNumber(Timestamp)));
//         Values.Add(MakeShareable(new FJsonValueNumber(Value)));
//     }

//     // Add the arrays to the JSON object
//     JsonObject->SetArrayField("timestamps", Timestamps);
//     JsonObject->SetArrayField("values", Values);

//     // Convert the JSON object to a string
//     FString Content;
//     TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Content);
//     FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

//     // Send the data to the Python server
//     SendRequest("http://localhost:5000/plot_line_chart", "POST", Content, "application/json");

//     return Content;
// }


// void AMyHttpClient::UpdateChartData()
// {
//     // This function updates the chart data when called
//     // For example, you might increment one of the y-values
//     Values[0] = MakeShareable(new FJsonValueNumber(Values[0]->AsNumber() + 1));  // Increment the first y-value

//     // Now send the updated data to the Python server
//     FString Url = "http://localhost:5000/plot_line_chart";
//     FString Verb = "POST";
//     FString ContentType = "application/json";
//     FString Body = GenerateLineChartData();  // Assume this function now uses the updated ChartData

//     SendRequest(Url, Verb, Body, ContentType);
// }


