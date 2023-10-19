// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/JR_GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/JR_MainMenuWD.h"



void AJR_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetOwningPlayerController();
	
	if (!IsValid(PlayerController)) return;

	InitializeMainMenu();
}

void AJR_GameHUD::InitializeMainMenu()
{
	if (!MainMenuWDClass.IsNull())
	{
		MainMenuWD = CreateWidget<UJR_MainMenuWD>(GetWorld(), MainMenuWDClass.LoadSynchronous());
    
		if (IsValid(MainMenuWD))
		{
			MainMenuWD->AddToViewport();
		}
	}
	
	SetFocusToWidget(MainMenuWD);
}

void AJR_GameHUD::SetFocusToWidget(UUserWidget* Widget)
{
	if( IsValid(Widget) )
	{
		FInputModeUIOnly InputModeUIOnly;
		InputModeUIOnly.SetWidgetToFocus(Widget->TakeWidget());
		
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(InputModeUIOnly);
	}
}
