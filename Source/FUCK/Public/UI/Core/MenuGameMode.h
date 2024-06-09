// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UI/Menu/MainMenu.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API AMenuGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AMenuGameMode();
	virtual void InitializeHUDForPlayer_Implementation(APlayerController* NewPlayer) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UMainMenu> MainMenuWidgetClass; 
};
