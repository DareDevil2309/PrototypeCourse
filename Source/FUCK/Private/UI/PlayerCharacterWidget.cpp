// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerCharacterWidget.h"

void UPlayerCharacterWidget::Init(APlayerCharacter* PlayerCharacter)
{
	Super::Init(PlayerCharacter);
	PlayerCharacter->XPController->OnXPChanged.AddUObject(this, &UPlayerCharacterWidget::OnXPChanged);
	PlayerCharacter->XPController->OnMaxXPChanged.AddUObject(this, &UPlayerCharacterWidget::OnMaxXPChanged);
	PlayerCharacter->XPController->OnLevelChanged.AddUObject(this, &UPlayerCharacterWidget::OnLevelChanged);
}

void UPlayerCharacterWidget::OnXPChanged(const float Value)
{
	XP = Value;
	UpdateProgress();
}

void UPlayerCharacterWidget::OnMaxXPChanged(const float Value)
{
	MaxXP = Value;
	UpdateProgress();
}

void UPlayerCharacterWidget::OnLevelChanged(const int Value)
{
	Level = Value;
	UpdateProgress();
}

void UPlayerCharacterWidget::UpdateProgress() const
{
	XPProgressBar->SetPercent(XP / MaxXP);
}


