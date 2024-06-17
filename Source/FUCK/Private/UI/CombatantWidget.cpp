// Fill out your copyright notice in the Description page of Project Settings.


#include "FUCK/Public/UI/CombatantWidget.h"

void UCombatantWidget::Init(ACombatant* Combatant)
{
	Health = Combatant->GetHealth();
	MaxHealth = Combatant->GetMaxHealth();
	OnHealthInited();
	Combatant->HealthChanged.AddUObject(this, &UCombatantWidget::OnHealthChanged);
	Combatant->MaxHealthChanged.AddUObject(this, &UCombatantWidget::OnMaxHealthChanged);
}

void UCombatantWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCombatantWidget::OnHealthChanged(const float Value)
{
	Health = Value;
	OnHealthUpdated();
}

void UCombatantWidget::OnMaxHealthChanged(const float Value)
{
	MaxHealth = Value;
	OnMaxHealthUpdated();
}
