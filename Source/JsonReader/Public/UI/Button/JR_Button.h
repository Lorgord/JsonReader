// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JR_Button.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressed, int, ButtonIndex);



class UButton;
class UTextBlock;



UCLASS(Blueprintable)
class JSONREADER_API UJR_Button : public UUserWidget
{
	GENERATED_BODY()
	
//constructors
private:
	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

//c++ private values
	int ButtonIndex = 0;

//blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Button|Init")
	void InitializeButton(int LButtonIndex);

	UFUNCTION(BlueprintCallable, Category = "Button|Text")
	void SetButtonText(FText Text);

	UFUNCTION(BlueprintNativeEvent, Category = "Button|Action")
	void OnButtonPressed();
	virtual void OnButtonPressed_Implementation();

	
//blueprint values
	UPROPERTY(BlueprintAssignable, Category = "Button|Action")
	FOnButtonPressed OnButtonPressedEvent;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Button|Button")
	UButton* Button;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Button|Text")
	UTextBlock* ButtonText;
};
