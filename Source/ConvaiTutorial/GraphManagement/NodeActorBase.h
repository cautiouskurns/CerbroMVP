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

	// Parent topic of this node, null if this node is a topic
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node")
	ANodeActorBase* ParentTopic;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node")
	ANodeActorBase* ParentSection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node")
	bool bIsHighlighted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subtopic")
	FString SubtopicContent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subtopic")
	FString SubtopicTitle;


	void SetNodeText(const FString& NewText);
	void SetNodeTextAndContent(const FString& Text, const FString& Content);
	void SetNodeTextFontSize(float FontSize);
	
	void SetNodeSize(float NodeSize);

	void SetNodeTextFontColor(FColor Color);
	void SetNodeMaterial(UMaterialInterface* Material);
	UStaticMeshComponent* GetStaticMeshComponent() const;

	void HighlightNode();
	void RestoreNodeOpacity();
	void LowerNodeOpacity();
};
