// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FUCK/PlayerCharacter.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API AGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	AGameHUD();
protected:
	virtual void BeginPlay() override;
	APlayerCharacter* PlayerCharacter;
};