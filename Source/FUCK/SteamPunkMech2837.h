// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "SteamPunkMech2837.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API ASteamPunkMech2837 : public AEnemyBase
{
	GENERATED_BODY()

public:

	ASteamPunkMech2837();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCapsuleComponent* DamageCollision;


	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> MagicSpell;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> LongAttackAnimation;
	
protected:
	void StateChaseClose();
	void MoveForward();

	void LongAttack(bool Rotate = true);
	void MagicAttack(bool Rotate = true);

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MagicSpell_Cooldown;
	float MagicSpell_Timestamp;

	void StateAttack();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ForwardSpeedAttack;
};
