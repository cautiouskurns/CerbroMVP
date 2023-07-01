// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReadWriteJsonFile.h"
#include "Json.h"
#include <Components/TreeView.h>
#include "BaseGameInstance.generated.h"



USTRUCT(BlueprintType)
struct FSubjectStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SubjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSectionStruct> SubjectDetailsArray;
};


UCLASS()
class CONVAITUTORIAL_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBaseGameInstance();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSubjectStruct> SubjectDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSectionStruct> SectionDataArray;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void InitializeSubjectDataArray();



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	FSubjectStruct SubjectData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FTopic> TopicDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FSubtopic> SubTopicDataArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FTest> QuestionDataArray;



	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FSectionStruct SectionStruct;

	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FTopic TopicStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "My Category")
	TArray<FSubtopic> SubTopicStructArray;

	UPROPERTY(BlueprintReadWrite, Category = "Your Category")
	FTest QuestionStruct;


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor PrimaryColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor SecondaryColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor TertiaryColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor AccentColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Color Palette")
	FColor BackgroundColor;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Information Structs")
	TArray<FTreeViewItem> TreeDataArray;

	//UFUNCTION(BlueprintCallable, Category = "Information Structs")
	//void PopulateTreeView(UTreeView* TreeView);

	//UFUNCTION(BlueprintCallable, Category = "Information Structs")
	//TArray<FListViewItem> GetListData();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 UpdateRandomQuestionTimesTested(int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	int32 UpdateTimesCorrect(int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer);

};
