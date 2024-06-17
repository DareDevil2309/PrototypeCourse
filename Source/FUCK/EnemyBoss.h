#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyBoss.generated.h"

/**
 *
 */
UCLASS()
class FUCK_API AEnemyBoss : public AEnemyBase
{


	GENERATED_BODY()

public:

	AEnemyBoss();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCapsuleComponent* DamageCollisionForHand;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCapsuleComponent* DamageCollisionForLongAttack;

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> MagicSpell;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "LongAttackDamage")
	void Explosion();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "MagicAttackIndex")
	int MagicIndex = 0;

protected:
	void StateChaseClose();

	void StateLongBossAttack();

	virtual void TickStateMachine();

	void MoveForward();

	void LongAttack(bool Rotate = true);

	UFUNCTION(BlueprintCallable, Category = "MagicAttack")
	void MagicAttack(bool Rotate = true);

	UFUNCTION(BlueprintCallable, Category = "MagicAttack")
	void IncreaseMagicIndex();

	UFUNCTION(BlueprintCallable, Category = "MagicAttack")
	void ReloadMagicIndex();

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float LongAttack_Cooldown;
	float LongAttack_Timestamp;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MagicSpell_Cooldown;
	float MagicSpell_Timestamp;

	void StateAttack();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ForwardSpeedAttack;
};
