// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JsonReader/JR_JsonReader.h"
#include "Serialization/JsonSerializer.h"




bool UJR_JsonReader::ReadJsonFileAsArray2D(const FString FileName, TArray<TArray<int>>& OutArray, FString ArrayName)
{
	FString JsonString = "";

	if (!ReadJsonFileAsString(FileName, JsonString))
	{
		return false;
	}
	
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), JsonObject))
	{
		return false;
	}
	
	auto ObjectArray = JsonObject->GetArrayField(ArrayName);

	if (ObjectArray.IsEmpty())
	{
		return false;
	}

	for (int i = 0; i <= ObjectArray.Num() - 1; ++i)
	{
		if (!OutArray.IsValidIndex(i)) continue;
	
		TArray<TSharedPtr<FJsonValue>>* InnerArray;
		ObjectArray[i]->TryGetArray(InnerArray);
		
		for (int j = 0; j <= InnerArray->Num() - 1; j++)
		{
			int Number;
			ObjectArray[i].Get()->AsArray()[j]->TryGetNumber(Number);
			
			if (!OutArray[i].IsValidIndex(j)) continue;
			
			OutArray[i][j] = Number;
		}
	}
	
	return true;
}

bool UJR_JsonReader::ReadJsonFileAsString(const FString FileName, FString& OutString)
{
	const FString JsonPath = FPaths::ProjectContentDir() + "Json/" + FileName;
	
	if( !FPlatformFileManager::Get().GetPlatformFile().FileExists(*JsonPath) )
	{
		return false;
	}
	
	if ( !FFileHelper::LoadFileToString(OutString, *JsonPath))
	{
		return false;
	}

	return true;
}
