// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Android.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API AAndroid : public AEnemyBase
{
	GENERATED_BODY()

public:

	AAndroid();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> LongAttackAnimations;
	FORCEINLINE class UStaticMeshComponent* GetWeapon() const { return Weapons; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UStaticMeshComponent* Weapons;
protected:

	void StateChaseClose();
	void LongAttack(bool Rotate = true);
	void MoveForward();

private:

	UPROPERTY(EditAnywhere, Category = "Combat")
	float LongAttack_Cooldown;
	float LongAttack_Timestamp;
	float LongAttack_ForwardSpeed;

	void StateAttack();
};
