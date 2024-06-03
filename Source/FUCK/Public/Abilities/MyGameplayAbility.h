// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EMyAbilityActivationPolicy
{
	OnInputTriggered,
	WhileInputActive,
	OnSpawn
};

UENUM(BlueprintType)
enum class EMyAbilityActivationGroup
{
	Independent,
	Exclusive_Replaceable,
	Exclusive_Blocking,
	MAX UMETA(Hidden)
};
/**
 * 
 */
UCLASS()
class FUCK_API UMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
};
