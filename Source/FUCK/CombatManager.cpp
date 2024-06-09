// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"

// Sets default values for this component's properties
UCombatManager::UCombatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	attackCooldown = 1.0f;

}


// Called when the game starts
void UCombatManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(attackCDHandle, this, &UCombatManager::NextAttacker, attackCooldown, true);
}


// Called every frame
void UCombatManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatManager::Timer() 
{
	if (attackResource < 100.0f) 
	{
		attackResource += 15.0f;
	}
}
void UCombatManager::NextAttacker()
{
	if (owner->NearbyEnemies.Num() > 0)
	{
		AEnemyBase* _enemyRef = Cast<AEnemyBase>(owner->NearbyEnemies[FMath::RandRange(0, owner->NearbyEnemies.Num() - 1)]);
		_enemyRef->isAttackTurn = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, tempRef->GetName());
	}
}




