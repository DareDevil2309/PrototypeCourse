#include "EnemyBoss.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.h"

AEnemyBoss::AEnemyBoss()
{
	DamageCollisionForHand = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hand Attack"));
	DamageCollisionForHand->InitCapsuleSize(42.0f, 96.0f);
	DamageCollisionForHand->SetupAttachment(GetMesh(), "Hand Attack");
	DamageCollisionForHand->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	DamageCollisionForLongAttack = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Long Attack"));
	DamageCollisionForLongAttack->InitCapsuleSize(42.0f, 96.0f);
	DamageCollisionForLongAttack->SetupAttachment(GetMesh(), "Long Attack");
	DamageCollisionForLongAttack->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	MagicSpell_Cooldown = 15.0f;
	MagicSpell_Timestamp = -MagicSpell_Cooldown;
	LongAttack_Cooldown = 10.0f;
	LongAttack_Timestamp = -LongAttack_Cooldown;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	Interruptable = false;
}


void AEnemyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickStateMachine();
}

void AEnemyBoss::TickStateMachine()
{
	if (!TargetDead)
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

		case State::LongBossAttack:
			StateLongBossAttack();
			break;

		case State::DEAD:
			if (!pStateDeadExecuted)
			{
				StateDead();
				pStateDeadExecuted = true;
			}
			break;
		}
	}
}

void AEnemyBoss::StateChaseClose()
{

	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	AAIController* AIController = Cast<AAIController>(Controller);

	FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();

	float DotProduct = FVector::DotProduct(GetActorForwardVector(), TargetDirection.GetSafeNormal());

	if (Distance > 300.0f && UGameplayStatics::GetTimeSeconds(GetWorld()) >= LongAttack_Timestamp + LongAttack_Cooldown && AIController->LineOfSightTo(Target) && isAttackTurn == true)
	{
		isAttackTurn = false;
		LongAttack_Timestamp = UGameplayStatics::GetTimeSeconds(GetWorld());
		LongAttack(true);
		return;
	}

	if (Distance <= 900.0f && DotProduct >= 0.95f && isAttackTurn == true)
	{
		isAttackTurn = false;

		if (Distance <= 300.0f)
		{
			Attack(true);
			return;
		}

		else if (Distance >= 600 && UGameplayStatics::GetTimeSeconds(GetWorld()) >= MagicSpell_Timestamp + MagicSpell_Cooldown && AIController->LineOfSightTo(Target))
		{
			MagicSpell_Timestamp = UGameplayStatics::GetTimeSeconds(GetWorld());
			MagicAttack(true);
			return;
		}
		
	}

	if (!AIController->IsFollowingAPath())
	{
		AIController->MoveToActor(Target);
	}
}

void AEnemyBoss::StateLongBossAttack()
{
	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	if (Distance < 150.0f)
	{
		Explosion();
		GetCharacterMovement()->MaxWalkSpeed = 350.0f;
		EndAttack();
	}
	else {
		if (AttackDamaging)
		{

			TSet<AActor*> OverlappingActors;
			DamageCollisionForLongAttack->GetOverlappingActors(OverlappingActors);

			for (AActor* OtherActor : OverlappingActors)
			{
				if (OtherActor == this)
				{
					continue;
				}
				if (!AttackHitActors.Contains(OtherActor))
				{
					float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, ClassDamage, GetController(), this, UDamageType::StaticClass());

					if (Target && dynamic_cast<APlayerCharacter*>(Target)->Dead)
					{
						TargetDead = true;
						return;
					}

					if (AppliedDamage > 0.0f)
					{
						AttackHitActors.Add(OtherActor);
					}
				}
			}
		}
	}
}

void AEnemyBoss::MoveForward()
{
	auto NewLocation = GetActorLocation() + (GetActorForwardVector() * ForwardSpeedAttack * GetWorld()->GetDeltaSeconds());
	SetActorLocation(NewLocation);
}

void AEnemyBoss::StateAttack()
{
	if (AttackDamaging)
	{

		TSet<AActor*> OverlappingActors;
		DamageCollisionForHand->GetOverlappingActors(OverlappingActors);

		for (AActor* OtherActor : OverlappingActors)
		{
			if (OtherActor == this)
			{
				continue;
			}
			if (!AttackHitActors.Contains(OtherActor))
			{
				float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, ClassDamage, GetController(), this, UDamageType::StaticClass());

				if (Target && dynamic_cast<APlayerCharacter*>(Target)->Dead)
				{
					TargetDead = true;
					return;
				}

				if (AppliedDamage > 0.0f)
				{
					AttackHitActors.Add(OtherActor);
				}
			}
		}
	}

	if (MovingForward)
	{
		MoveForward();
	}
}

void AEnemyBoss::LongAttack(bool Rotate)
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;;
	SetState(State::LongBossAttack);
	AttackDamaging = true;
	AAIController* AIController = Cast<AAIController>(Controller);
	AIController->MoveToActor(Target);
}

void AEnemyBoss::MagicAttack(bool Rotate)
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

	PlayAnimMontage(MagicSpell[0]);
}

void AEnemyBoss::IncreaseMagicIndex()
{
	++MagicIndex;
}

void AEnemyBoss::ReloadMagicIndex()
{
	MagicIndex = 0;
}


