// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JR_JsonReader.generated.h"


UCLASS()
class JSONREADER_API UJR_JsonReader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	static bool ReadJsonFileAsArray2D(const FString FileName, TArray<TArray<int>>& OutArray, FString ArrayName);

	static bool ReadJsonFileAsString(const FString FileName, FString& OutString);
};
