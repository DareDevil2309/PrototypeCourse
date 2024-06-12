// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "Kismet/GameplayStatics.h"

void UPauseMenu::Init()
{
	GetOwningPlayer()->SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::Resume);
	OptionsButton->OnClicked.AddDynamic(this, &UPauseMenu::ShowOptions);
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::Exit);
	SaveButton->OnClicked.AddDynamic(this, &UPauseMenu::Save);
}

void UPauseMenu::Resume()
{
	ResumeButton->OnClicked.RemoveDynamic(this, &UPauseMenu::Resume);
	OptionsButton->OnClicked.RemoveDynamic(this, &UPauseMenu::ShowOptions);
	QuitButton->OnClicked.RemoveDynamic(this, &UPauseMenu::Exit);
	SaveButton->OnClicked.RemoveDynamic(this, &UPauseMenu::Save);
	
	this->RemoveFromParent();
	GetOwningPlayer()->SetShowMouseCursor(false);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UPauseMenu::ShowOptions()
{
}

void UPauseMenu::Exit()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MainMenuMap, false);
}

void UPauseMenu::Save()
{
}
