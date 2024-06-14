// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamPunkMech2837.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.h"

ASteamPunkMech2837::ASteamPunkMech2837()
{
	DamageCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	DamageCollision->InitCapsuleSize(42.0f, 96.0f);
	DamageCollision->SetupAttachment(GetMesh(), "core");
	DamageCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	MagicSpell_Cooldown = 15.0f;
	MagicSpell_Timestamp = -MagicSpell_Cooldown;
	LongAttack_Cooldown = 5.0f;
	LongAttack_Timestamp = -LongAttack_Cooldown;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
}

void ASteamPunkMech2837::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickStateMachine();
}

void ASteamPunkMech2837::StateChaseClose()
{

	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	AAIController* AIController = Cast<AAIController>(Controller);

	FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();

	float DotProduct = FVector::DotProduct(GetActorForwardVector(), TargetDirection.GetSafeNormal());

	if (Distance <= 900.f && DotProduct >= 0.95f && isAttackTurn == true)
	{
		isAttackTurn = false;
		if (Distance <= 300.0f)
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
		else if (Distance > 300 && UGameplayStatics::GetTimeSeconds(GetWorld()) >= LongAttack_Timestamp + LongAttack_Cooldown && AIController->LineOfSightTo(Target))
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

void ASteamPunkMech2837::LongAttack(bool Rotate)
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
	PlayAnimMontage(LongAttackAnimation[0]);
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

