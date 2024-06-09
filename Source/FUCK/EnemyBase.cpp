#include "EnemyBase.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/BlueprintTypeConversions.h"

AEnemyBase::AEnemyBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HPBar = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("HealthBar"));
	HPBar->SetupAttachment(GetMesh());

	PrimaryActorTick.bCanEverTick = true;
	MovingForward = false;
	MovingBackwards = false;
	Interruptable = true;
	LastStumbleIndex = 0;
}

void AEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	HPBar->SetWidgetClass(CombatantWidgetClass);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	ActiveState = State::IDLE;

	Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (CombatantWidgetClass)
	{
		if (const auto CombatantWidget = Cast<UCombatantWidget>(CreateWidget(GetGameInstance(), CombatantWidgetClass)))
		{
			CombatantWidget->Init(this);
			HPBar->SetWidget(CombatantWidget);
		}
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::TickStateMachine()
{
	switch (ActiveState)
	{
	case State::IDLE:
		StateIdle();
		break;

	case State::CHASE_CLOSE:
		StateChaseClose();
		break;

	case State::CHASE_FAR:
		StateChaseFar();
		break;

	case State::ATTACK:
		StateAttack();
		break;

	case State::STUMBLE:
		StateStumble();
		break;

	case State::TAUNT:
		StateTaunt();
		break;

	case State::DEAD:
		StateDead();
		break;
	}

}

void AEnemyBase::SetState(State NewState)
{
	if (ActiveState != State::DEAD)
	{
		ActiveState = NewState;
	}
}

void AEnemyBase::StateIdle()
{
	if (Target && FVector::Distance(Target->GetActorLocation(), GetActorLocation()) <= 1200.0f)
	{
		TargetLocked = true;

		SetState(State::CHASE_CLOSE);
	}
}

void AEnemyBase::StateChaseClose()
{

}

void AEnemyBase::StateChaseFar()
{
	if (FVector::Distance(GetActorLocation(), Target->GetActorLocation()) <= 850.0f)
	{
		SetState(State::CHASE_CLOSE);
	}
}

void AEnemyBase::StateAttack()
{
}

void AEnemyBase::Death()
{
	Super::Death();
	HealthChanged.Broadcast(0.0f);
	int AnimationIndex;
	AnimationIndex = FMath::RandRange(0, DeathAnimations.Num() - 1);
	PlayAnimMontage(DeathAnimations[AnimationIndex]);
}

void AEnemyBase::StateStumble()
{
	if (Stumbling) {

		if (MovingBackwards)
		{
			AddMovementInput(-GetActorForwardVector(), 40.0f * GetWorld()->GetDeltaSeconds());
		}
	}

	else
	{
		SetState(State::CHASE_CLOSE);
	}
}

void AEnemyBase::StateTaunt()
{

}

void AEnemyBase::StateDead()
{
	Cast<AAIController>(Controller)->StopMovement();
}

void AEnemyBase::FocusTarget()
{
	AAIController* Control = Cast<AAIController>(GetController());
	Control->SetFocus(Target);
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (ActiveState != State::DEAD)
	{
		CurrentHealth -= DamageAmount;
		if (DamageCauser == this)
		{
			return 0.0f;
		}

		if (CurrentHealth <= 0.0f)
		{
			Death();
			SetState(State::DEAD);
			return DamageAmount;
		}

		HealthChanged.Broadcast(CurrentHealth);
		
		if (!Interruptable)
		{
			return DamageAmount;
		}

		EndAttack();
		SetMovingBackwards(false);
		SetMovingForward(false);
		Stumbling = true;
		SetState(State::STUMBLE);
		Cast<AAIController>(Controller)->StopMovement();
		int AnimationIndex;
		do
		{
			AnimationIndex = FMath::RandRange(0, TakeHit_StumbleBackwards.Num() - 1);
		} while (AnimationIndex == LastStumbleIndex);

		LastStumbleIndex = AnimationIndex;

		PlayAnimMontage(TakeHit_StumbleBackwards[AnimationIndex]);
		FVector Direction = DamageCauser->GetActorLocation() - GetActorLocation();
		Direction = FVector(Direction.X, Direction.Y, 0);
		FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		SetActorRotation(Rotation);
	}
	
	return DamageAmount;
}

void AEnemyBase::MoveForward()
{
	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * 500.0f * GetWorld()->GetDeltaSeconds());

	SetActorLocation(NewLocation, true);

}

void AEnemyBase::Attack(bool Rotate)
{
	Super::Attack();

	SetMovingBackwards(false);
	SetMovingForward(false);
	SetState(State::ATTACK);
	Cast<AAIController>(Controller)->StopMovement();

	if (Rotate)
	{
		FVector Direction = Target->GetActorLocation() - GetActorLocation();
		Direction = FVector(Direction.X, Direction.Y, 0);

		FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		SetActorRotation(Rotation);
	}

	int RandomIndex = FMath::RandRange(0, AttackAnimations.Num() - 1);
	PlayAnimMontage(AttackAnimations[RandomIndex]);
}

void AEnemyBase::AttackNextReady()
{
	Super::AttackNextReady();
}

void AEnemyBase::EndAttack()
{
	Super::EndAttack();
	SetState(State::CHASE_CLOSE);
}

void AEnemyBase::AttackLunge()
{
	Super::AttackLunge();
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
