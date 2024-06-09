// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Combatant.generated.h"


UCLASS()
class FUCK_API ACombatant : public ACharacter
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_OneParam(FHealthChangedSignature, float);

public:
	// Sets default values for this character's properties
	ACombatant(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float GetHealth();
	float GetMaxHealth();
	FHealthChangedSignature HealthChanged;
	FHealthChangedSignature MaxHealthChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	AActor* Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool TargetLocked;

	bool Attacking;
	bool AttackDamaging;
	bool MovingForward;
	bool MovingBackwards;
	bool NextAttackReady;
	bool Stumbling;

	bool RotateTowardsTarget;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float RotationSmoothing;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> AttackAnimations;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> TakeHit_StumbleBackwards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> DeathAnimations;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Health")
	float CurrentHealth;
	
	UPROPERTY(EditAnywhere,BluePrintReadWrite, Category = "Damage")
	float ClassDamage;
	// Actors hit with the last attack - Used to stop duplicate hits
	TArray<AActor*> AttackHitActors;

	virtual void Attack();

	// anim called: rotate and jump towards target
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void AttackLunge();

	// anim called: rotate and jump towards target
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void EndAttack();

	// set if weapon applies damage
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void SetAttackDamaging(bool Damaging);

	// anim called: set if moving forward
	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void SetMovingForward(bool IsMovingForward);

	// anim called: set if moving backwards
	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void SetMovingBackwards(bool IsMovingBackwards);

	// anim called: set if moving backwards
	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual void EndStumble();

	// called by anim to singlat that the next attack is potentially allowed
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AttackNextReady();

	virtual void LookAtSmooth();

	// anim called: get rate of actors look rotation
	UFUNCTION(BlueprintCallable, Category = "Animation")
	float GetCurrentRotationSpeed();

	virtual void Death();

	float LastRotationSpeed;

};
