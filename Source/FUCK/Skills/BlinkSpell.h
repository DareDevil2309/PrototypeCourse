// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include <NiagaraFunctionLibrary.h>
#include <NiagaraComponent.h>
#include "BlinkSpell.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UBlinkSpell : public USkillBase
{
	GENERATED_BODY()

public:
	UBlinkSpell();

	UPROPERTY(EditAnywhere)
	float distance;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* effectVFXClass;

	UNiagaraComponent* effectVFX;

	void Cast_Implementation() override;

};
