// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamPunkMech2837.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ASteamPunkMech2837::ASteamPunkMech2837()
{
	DamageCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	DamageCollision->InitCapsuleSize(42.0f, 96.0f);
	DamageCollision->SetupAttachment(GetMesh(), "core");
	DamageCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	MagicSpell_Cooldown = 15.0f;
	MagicSpell_Timestamp = -MagicSpell_Cooldown;
}

void ASteamPunkMech2837::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickStateMachine();
}

void ASteamPunkMech2837::TickStateMachine()
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


void ASteamPunkMech2837::Attack(bool Rotate)
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
	AAIController* AIController = Cast<AAIController>(Controller);
	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	ForwardSpeedAttack = Distance + 400.0f;
	PlayAnimMontage(AttackAnimations[0]);
}

void ASteamPunkMech2837::StateChaseClose()
{

	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	AAIController* AIController = Cast<AAIController>(Controller);

	FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();

	float DotProduct = FVector::DotProduct(GetActorForwardVector(), TargetDirection.GetSafeNormal());

	if (Distance <= 900.f && DotProduct >= 0.95f)
	{
		if (Distance <= 300.f)
		{
			Attack(true);
			return;
		}
		else if (UGameplayStatics::GetTimeSeconds(GetWorld()) >= MagicSpell_Timestamp + MagicSpell_Cooldown && AIController->LineOfSightTo(Target))
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

void ASteamPunkMech2837::MoveForward()
{
	auto NewLocation = GetActorLocation() + (GetActorForwardVector() * ForwardSpeedAttack * GetWorld()->GetDeltaSeconds());
	SetActorLocation(NewLocation);
}

void ASteamPunkMech2837::StateAttack()
{
	if (AttackDamaging)
	{

		TSet<AActor*> OverlappingActors;
		DamageCollision->GetOverlappingActors(OverlappingActors);

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

void ASteamPunkMech2837::MagicAttack(bool Rotate)
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

