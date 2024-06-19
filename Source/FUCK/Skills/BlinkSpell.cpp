// Fill out your copyright notice in the Description page of Project Settings.


#include "BlinkSpell.h"

UBlinkSpell::UBlinkSpell()
{
	cooldown = 3.0f;
	distance = 1000.f;
}

void UBlinkSpell::Cast_Implementation()
{
	effectVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effectVFXClass, player->GetActorLocation() + FVector(0, 0, 0), FRotator(0.f));
	FVector _movement = player->GetVelocity();
	_movement = _movement.GetSafeNormal2D();
	player->SetActorLocation(player->GetActorLocation() + _movement * distance, true);
	effectVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effectVFXClass, player->GetActorLocation() + FVector(0, 0, 0), FRotator(0.f));
}