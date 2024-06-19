// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include <NiagaraFunctionLibrary.h>
#include <NiagaraComponent.h>
#include "HealSpell.generated.h"


/**
 * 
 */
UCLASS()
class FUCK_API UHealSpell : public USkillBase
{
	GENERATED_BODY()

public:
	UHealSpell();

	UPROPERTY(EditAnywhere)
	float healRate;

	UPROPERTY(EditAnywhere)
	float samplingStep;
	
	UPROPERTY(EditAnywhere)
	float duration;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* effectVFXClass;

	UNiagaraComponent* effectVFX;

	void Cast_Implementation() override;

	FTimerHandle timerHandler;
	FTimerHandle durationHandler;

	void OnTimer();	

	void OnEnd();
	
};
