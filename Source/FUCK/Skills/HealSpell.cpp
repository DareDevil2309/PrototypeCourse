// Fill out your copyright notice in the Description page of Project Settings.


#include "HealSpell.h"

UHealSpell::UHealSpell()
{
	cooldown = 15.0f;
	healRate = 1000.f;
	samplingStep = 0.2f;
	duration = 5.f;
}

void UHealSpell::Cast_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &UHealSpell::OnTimer, samplingStep, true);
	GetWorld()->GetTimerManager().SetTimer(durationHandler, this, &UHealSpell::OnEnd, duration, false);
	effectVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(effectVFXClass, player->GetMesh(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
}

void UHealSpell::OnTimer()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(player->GetHealth()));
	player->SetHealth(player->GetHealth()+healRate*samplingStep);
}

void UHealSpell::OnEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(timerHandler);
	effectVFX->Deactivate();
}
