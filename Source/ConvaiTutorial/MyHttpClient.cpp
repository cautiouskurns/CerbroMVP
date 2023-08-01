// Fill out your copyright notice in the Description page of Project Settings.

#include "Http.h"
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

void AMyHttpClient::SendRequest(FString Url, FString Verb, FString Content, FString ContentType)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(Url);
    HttpRequest->SetVerb(Verb);
    HttpRequest->SetHeader(TEXT("User-Agent"), "MyClient/1.0");
    HttpRequest->SetHeader(TEXT("Content-Type"), ContentType);
    HttpRequest->SetContentAsString(Content);
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMyHttpClient::OnResponseReceived);
    HttpRequest->ProcessRequest();
}

void AMyHttpClient::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if(!EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        // Handle error here
        return;
    }
    
    // Log or do something with the response
    UE_LOG(LogTemp, Warning, TEXT("Response: %s"), *Response->GetContentAsString());
}

void AMyHttpClient::TestCommunication()
{
    SendRequest("http://localhost:5000/process_data", "POST", 
    "{\"key1\":\"value1\", \"key2\":\"value2\"}", "application/json");
}
