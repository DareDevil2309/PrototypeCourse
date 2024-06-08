// Fill out your copyright notice in the Description page of Project Settings.


#include "Android.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"


AAndroid::AAndroid()
{
	Weapons = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	Weapons->SetupAttachment(GetMesh(), "RightHandItem");
	Weapons->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	LongAttack_Cooldown = 15.0f;
	LongAttack_Timestamp = -LongAttack_Cooldown;
}

void AAndroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickStateMachine();
}

void AAndroid::TickStateMachine()
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

void AAndroid::StateChaseClose()
{
	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	AAIController* AIController = Cast<AAIController>(Controller);

	FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();

	float DotProduct = FVector::DotProduct(GetActorForwardVector(), TargetDirection.GetSafeNormal());

	if (Distance <= 900.f && DotProduct >= 0.95f)
	{
		if (Distance <= 300.f)
		{
			Attack(false);
			return;
		}
		else if (UGameplayStatics::GetTimeSeconds(GetWorld()) >= LongAttack_Timestamp + LongAttack_Cooldown && AIController->LineOfSightTo(Target))
		{
			LongAttack_Timestamp = UGameplayStatics::GetTimeSeconds(GetWorld());
			LongAttack(true);
			return;
		}
	}
	if (!AIController->IsFollowingAPath())
	{
		AIController->MoveToActor(Target);
	}
}

void AAndroid::LongAttack(bool Rotate)
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

	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	LongAttack_ForwardSpeed = Distance + 600.0f;
	PlayAnimMontage(LongAttackAnimations[0]);
}

void AAndroid::MoveForward()
{
	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * LongAttack_ForwardSpeed * GetWorld()->GetDeltaSeconds());

	SetActorLocation(NewLocation);
}

void AAndroid::StateAttack()
{
	if (AttackDamaging)
	{
		TSet<AActor*> OverlappingActors;
		Weapons->GetOverlappingActors(OverlappingActors);

		for (AActor* OtherActor : OverlappingActors)
		{
			if (OtherActor == this)
			{
				continue;
			}
			if (!AttackHitActors.Contains(OtherActor))
			{
				float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 1.0f, GetController(), this, UDamageType::StaticClass());

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

float AAndroid::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser != Target)
	{
		return 0.0f;
	}

	if (QuickHitsTaken == 0 || GetWorld()->GetTimeSeconds() - QuickHitsTimestamp <= 1.0f)
	{
		QuickHitsTaken++;
		QuickHitsTimestamp = GetWorld()->GetTimeSeconds();

		if (QuickHitsTaken >= 3)
		{
			Interruptable = false;
		}
	}
	else
	{
		QuickHitsTaken = 0;
		Interruptable = true;
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}