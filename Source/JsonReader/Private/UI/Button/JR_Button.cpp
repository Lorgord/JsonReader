// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Button/JR_Button.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


void UJR_Button::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnPressed.AddDynamic(this, &UJR_Button::OnButtonPressed);
}

void UJR_Button::NativeDestruct()
{
	Super::NativeDestruct();
	
	Button->OnPressed.RemoveDynamic(this, &UJR_Button::OnButtonPressed);
}



void UJR_Button::InitializeButton(int LButtonIndex)
{
	ButtonIndex = LButtonIndex;
	SetButtonText(FText::AsNumber(++LButtonIndex));
}

void UJR_Button::SetButtonText(FText Text)
{
	if ( !IsValid(ButtonText)) return;

	ButtonText->SetText(Text);
}

void UJR_Button::OnButtonPressed_Implementation()
{
	OnButtonPressedEvent.Broadcast(ButtonIndex);
}