// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JR_MainMenuWD.generated.h"

class UJR_Button;
class UButton;
class UTextBlock;
class UHorizontalBox;



UCLASS(Blueprintable)
class JSONREADER_API UJR_MainMenuWD : public UUserWidget
{
	GENERATED_BODY()

//constructors
private:
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

//c++ private methods
	
	void InitializeButtons();
	void FillArrayZeroed();
	void GetResult();

//c++ private values

	TArray<UJR_Button*> ButtonsContainer;
	
	TArray<TArray<int>> JsonArray2D;
	
	TTuple<int, int> PressedResult;

	bool bIsButtonPressedOnce = false;

//blueprint methods
public:


	UFUNCTION(BlueprintCallable, Category = "MainMenu|Output")
	void ClearOutput();

	UFUNCTION(BlueprintCallable, Category = "MainMenu|Output")
	void PrintOutput(FText Result);

	UFUNCTION(BlueprintCallable, Category = "MainMenu|Input")
	void UpdateSource();

	UFUNCTION(BlueprintNativeEvent, Category = "MainMenu|Input")
	void OnInputButtonPressed(int ButtonIndex);
	virtual void OnInputButtonPressed_Implementation(int ButtonIndex);

//blueprint values

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|Output")
	UTextBlock* OutputText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|Update")
	UButton* UpdateButton = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|Input")
	UHorizontalBox* ButtonsPanel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainMenu|Input")
	FString SourceFileName = "Numbers.json";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainMenu|Input")
	FString SourceFileArrayName = "Array";
};