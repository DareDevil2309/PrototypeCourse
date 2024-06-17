// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XPController.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FUCK_API UXPController : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_OneParam(FXPChangedSignature, float);
	DECLARE_MULTICAST_DELEGATE_OneParam(FLevelChangedSignature, int);

public:
	// Sets default values for this component's properties
	UXPController();
	void Init() const;
	FXPChangedSignature OnXPChanged;
	FXPChangedSignature OnMaxXPChanged;
	FLevelChangedSignature OnLevelChanged;

	void AddXP(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	int CurrentLevel = 0;
	float CurrentXP = 0.0f;
	float MaxXP = 1.0f;
	void TryLevelUp();
};
