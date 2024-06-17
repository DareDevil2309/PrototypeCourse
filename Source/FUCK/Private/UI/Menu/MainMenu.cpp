// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/MainMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::Init()
{
}

void UMainMenu::StartGame()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), StartLevel, false);
}

void UMainMenu::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UMainMenu::OpenSettings()
{
}
