// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/TextRenderActor.h>
#include <Components/TextRenderComponent.h>
#include "NodeActorBase.generated.h"


UCLASS()
class CONVAITUTORIAL_API ANodeActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node")
	UStaticMeshComponent* NodeMesh;

	// The root scene component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node")
	UTextRenderComponent* NodeTextComponent;

	UPROPERTY(EditAnywhere, Category = "Font")
	UFont* NodeFont;

	void SetNodeText(const FString& NewText);
	void SetFontSize(float FontSize);
	void SetFontColor(FColor Color);
	void SetMaterial(UMaterialInterface* Material);
	UStaticMeshComponent* GetStaticMeshComponent() const;
};
