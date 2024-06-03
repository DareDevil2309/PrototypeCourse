// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAttributeSet.h"
#include "../Abilities/MyAttributeSet.h"
#include "MyGameplayTags.h"
#include "HealthAttributeSet.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageSelfDestruct);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_FellOutOfWorld);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Lyra_Damage_Message);
/**
 * 
 */
UCLASS()
class FUCK_API UHealthAttributeSet : public UMyAttributeSet
{
	GENERATED_BODY()

public:
	UHealthAttributeSet();

	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Healing);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Damage);

	mutable FMyAttributeEvent OnHealthChanged;
	mutable FMyAttributeEvent OnMaxHealthChanged;
	mutable FMyAttributeEvent OnOutOfHealth;

protected:
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	// virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	// virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	// void ClampAttribute(const FGameplayAttribute& Attribute, float& newValue) const;
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;
private:
	UPROPERTY(BlueprintReadOnly, Category = "Helath", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "Helath", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	bool IsOutOfHealth;
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;
	
	UPROPERTY(BlueprintReadOnly, Category="Lyra|Health", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Healing;

	UPROPERTY(BlueprintReadOnly, Category="Lyra|Health", Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;
};
