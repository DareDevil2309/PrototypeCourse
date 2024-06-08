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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Finite State Machine")
	State ActiveState;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);

	int LastStumbleIndex;

protected:

	virtual void BeginPlay() override;

	virtual void TickStateMachine();

	void SetState(State NewState);

	virtual void StateIdle();
	virtual void StateChaseClose();
	virtual void StateChaseFar();

	virtual void StateAttack();

	void Death();
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
};

