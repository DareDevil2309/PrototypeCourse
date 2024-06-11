// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOver/UGameOverWidget.h"
#include "Kismet/GameplayStatics.h"

void UUGameOverWidget::Init()
{
	Inited();
}

void UUGameOverWidget::LoadMainMenu()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), MainMenuMap, false);
}
