// Fill out your copyright notice in the Description page of Project Settings.


#include "FUCK/Public/UI/GameHUD.h"

#include "Blueprint/UserWidget.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerController()->GetCharacter());
}
