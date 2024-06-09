// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combatant.h"
#include "PlayerCharacter.h"
#include "EnemyBase.h"
#include "CombatManager.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUCK_API UCombatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatManager();

	UPROPERTY(meta=(ClampMax=100.0))
	float attackResource;

	UPROPERTY(EditAnywhere)
	float attackCooldown;

	FTimerHandle timerHandle;

	FTimerHandle attackCDHandle;

	TArray<AEnemyBase*> possibleAttackers;

	APlayerCharacter* owner = Cast<APlayerCharacter>(GetOwner());

	void Timer();

	void NextAttacker();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
