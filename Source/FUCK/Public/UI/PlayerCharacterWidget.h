// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatantWidget.h"
#include "Components/ProgressBar.h"
#include "FUCK/PlayerCharacter.h"
#include "PlayerCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UPlayerCharacterWidget : public UCombatantWidget
{
	GENERATED_BODY()
public:
	void Init(APlayerCharacter* PlayerCharacter);

	UPROPERTY(meta = (BindWidget))
	UProgressBar* XPProgressBar;
private:
	TObjectPtr<APlayerCharacter> Player;
	float XP;
	float MaxXP;
	int Level;
	void OnXPChanged(float Value);
	void OnMaxXPChanged(float Value);
	void OnLevelChanged(int Value);
	void UpdateProgress() const;
};
