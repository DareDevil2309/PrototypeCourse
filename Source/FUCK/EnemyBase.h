#pragma once
#include "CoreMinimal.h"
#include "Combatant.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class State : uint8
{
	IDLE,CHASE_CLOSE,CHASE_FAR,ATTACK,STUMBLE,TAUNT,DEAD					
};

UCLASS()
class FUCK_API AEnemyBase : public ACombatant
{
	GENERATED_BODY()

public:

	AEnemyBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Finite State Machine")
	State ActiveState;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* OverheadSmash;

	int LastStumbleIndex;

	bool isAttackTurn = false;

protected:

	virtual void BeginPlay() override;

	virtual void TickStateMachine();

	void SetState(State NewState);

	virtual void StateIdle();

	// state: actively trying to keep close and attack the target
	virtual void StateChaseClose();

	// state: engaged but not currently trying to attack (idle behavior)
	virtual void StateChaseFar();

	virtual void StateAttack();

	virtual void StateStumble();

	virtual void StateTaunt();

	virtual void StateDead();

	virtual void MoveForward();

	virtual void Attack(bool Rotate = true);

	void AttackNextReady();

	void EndAttack();

	virtual void AttackLunge();

	bool Interruptable;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void FocusTarget();

	// returns weapon subobject
	FORCEINLINE class UStaticMeshComponent* GetWeapon() const { return Weapon; }

};

