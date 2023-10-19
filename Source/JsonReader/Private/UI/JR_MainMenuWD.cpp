// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonReader/Public/UI/JR_MainMenuWD.h"

#include "UI/Button/JR_Button.h"
#include "UI/JsonReader/JR_JsonReader.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"



void UJR_MainMenuWD::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateButton->OnPressed.AddDynamic(this, &UJR_MainMenuWD::UpdateSource);

	InitializeButtons();
	FillArrayZeroed();
	UpdateSource();
}

void UJR_MainMenuWD::NativeDestruct()
{
	Super::NativeDestruct();

	UpdateButton->OnPressed.RemoveDynamic(this, &UJR_MainMenuWD::UpdateSource);

	if (ButtonsContainer.IsEmpty()) return;

	for (auto Button : ButtonsContainer)
	{
		Button->OnButtonPressedEvent.RemoveDynamic(this, &UJR_MainMenuWD::OnInputButtonPressed);
	}
}



void UJR_MainMenuWD::InitializeButtons()
{
	if ( !IsValid(ButtonsPanel) ) return;
	
	ButtonsContainer.AddZeroed(6);
	
	int Index = 0;
	for (auto Widget : ButtonsPanel->GetAllChildren())
	{
		if ( UJR_Button* Button = Cast<UJR_Button>(Widget) )
		{
			Button->OnButtonPressedEvent.AddDynamic(this, &UJR_MainMenuWD::OnInputButtonPressed);
			Button->InitializeButton(Index);
			ButtonsContainer[Index] = Button;
			++Index;
		}
	}
}

void UJR_MainMenuWD::FillArrayZeroed()
{
	const int ButtonsNum = ButtonsContainer.Num();
	
	JsonArray2D.AddZeroed(ButtonsNum);

	for (int i = 0; i <= ButtonsNum - 1; ++i)
	{
		JsonArray2D[i].AddZeroed(ButtonsNum);
	}
}

void UJR_MainMenuWD::OnInputButtonPressed_Implementation(int ButtonIndex)
{
	if (!bIsButtonPressedOnce)
	{
		PressedResult.Key = ButtonIndex;
		bIsButtonPressedOnce = true;
		ClearOutput();
	}
	else
	{
		PressedResult.Value = ButtonIndex;
		bIsButtonPressedOnce = false;
		GetResult();
	}
}

void UJR_MainMenuWD::UpdateSource()
{
	if (SourceFileName == "") return;
	
	if (!UJR_JsonReader::ReadJsonFileAsArray2D(SourceFileName, JsonArray2D, SourceFileArrayName))
	{
		PrintOutput(FText::FromString("Unable to update source file, please check file path"));
	}
}

void UJR_MainMenuWD::GetResult()
{
	if (JsonArray2D.IsEmpty()) return;
	
	int Result = JsonArray2D[PressedResult.Key][PressedResult.Value];

	PrintOutput(FText::AsNumber(Result));
}

void UJR_MainMenuWD::PrintOutput(FText Result)
{
	if (!IsValid(OutputText)) return;

	OutputText->SetText(Result);
}

void UJR_MainMenuWD::ClearOutput()
{
	OutputText->SetText(FText());
}