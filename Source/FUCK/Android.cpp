// Fill out your copyright notice in the Description page of Project Settings.


#include "Android.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

AAndroid::AAndroid()
{
	Weapons = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	Weapons->SetupAttachment(GetMesh(), "RightHandItem");
	Weapons->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	LongAttack_Cooldown = 15.0f;
	LongAttack_Timestamp = -LongAttack_Cooldown;
	GetCharacterMovement()->MaxWalkSpeed = 450;
}

void AAndroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Super::TickStateMachine();
}


void AAndroid::StateChaseClose()
{
	float Distance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
	AAIController* AIController = Cast<AAIController>(Controller);

	FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();

	float DotProduct = FVector::DotProduct(GetActorForwardVector(), TargetDirection.GetSafeNormal());

	if (Distance <= 900.f && DotProduct >= 0.95f && isAttackTurn == true)
	{
		isAttackTurn = false;
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