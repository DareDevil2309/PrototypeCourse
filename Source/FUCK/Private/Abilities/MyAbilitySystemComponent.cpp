// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Abilities/MyAbilitySystemComponent.h"

UMyAbilitySystemComponent::UMyAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
	FMemory::Memset(ActivationGroupCounts, 0, sizeof(ActivationGroupCounts));
}
