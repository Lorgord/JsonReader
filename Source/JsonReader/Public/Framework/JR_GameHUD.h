// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JR_GameHUD.generated.h"

class UJR_MainMenuWD;

UCLASS()
class JSONREADER_API AJR_GameHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

//blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "GameHUD|MainMenuWD")
	void InitializeMainMenu();

	UFUNCTION(Blueprintable, Category = "GameHUD|Widgets")
	void SetFocusToWidget(UUserWidget* Widget);

//blueprint protected values
protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "GameMode|Controllers")
	APlayerController* PlayerController = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameMode|Widgets")
	TSoftClassPtr<UJR_MainMenuWD> MainMenuWDClass;

	UPROPERTY(BlueprintReadOnly, Category = "GameMode|Widgets")
	UJR_MainMenuWD* MainMenuWD = nullptr;
};
