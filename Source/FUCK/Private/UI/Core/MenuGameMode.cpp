// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Core/MenuGameMode.h"

#include "Blueprint/UserWidget.h"

AMenuGameMode::AMenuGameMode()
{
}

void AMenuGameMode::InitializeHUDForPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::InitializeHUDForPlayer_Implementation(NewPlayer);

	if (MainMenuWidgetClass)
	{
		if (auto Widget = Cast<UMainMenu>(CreateWidget(GetGameInstance(), MainMenuWidgetClass)))
		{
			Widget->Init();
			Widget->AddToViewport();
		}
	}
}
