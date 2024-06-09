// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FUCK/Combatant.h"
#include "CombatantWidget.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UCombatantWidget : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DELEGATE_OneParam(HealthChangeSignature, float)
	
public:
	void Init(ACombatant* Combatant);
	
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float MaxHealth;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health")
	void OnHealthInited();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health")
	void OnHealthUpdated();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Health")
	void OnMaxHealthUpdated();
	
protected:
	virtual void NativeConstruct() override;
private:
	TObjectPtr<ACombatant> Owner;
	void OnMaxHealthChanged(float Value);
	void OnHealthChanged(float Value);
};
