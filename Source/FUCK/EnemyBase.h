#pragma once
#include "CoreMinimal.h"
#include "Combatant.h"
#include "Components/WidgetComponent.h"
#include "UI/CombatantWidget.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class State : uint8
{
	IDLE,CHASE_CLOSE,CHASE_FAR,ATTACK,STUMBLE,TAUNT,DEAD, LongBossAttack
};

UCLASS()
class FUCK_API AEnemyBase : public ACombatant
{
	GENERATED_BODY()

public:

	AEnemyBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostInitializeComponents() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Finite State Machine")
	State ActiveState;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser);


	UPROPERTY(EditAnywhere, Category = "Health")
	TSubclassOf<class UCombatantWidget> CombatantWidgetClass;
	
	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Health")
	UWidgetComponent* HPBar;
	int LastStumbleIndex;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float HPBarShowDistance = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "XP")
	float XpOnDeath = 2.0f;

	bool isAttackTurn = false;
	

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

	bool TargetDead = false;

	bool Interruptable;

	bool pStateDeadExecuted = false;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void FocusTarget();
private:
	float CheckPlayerTime = 0.0f;
	float CheckPlayerTimeDelta = 0.5f;
	void CheckHPBarVisibility();
};

