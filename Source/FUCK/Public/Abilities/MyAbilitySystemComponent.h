// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyGameplayAbility.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UMyAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
private:
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
	int32 ActivationGroupCounts[(uint8)EMyAbilityActivationGroup::MAX];
};
