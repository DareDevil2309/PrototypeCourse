// Fill out your copyright notice in the Description page of Project Settings.


#include "XPController.h"


// Sets default values for this component's properties
UXPController::UXPController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UXPController::Init() const
{
	OnXPChanged.Broadcast(CurrentXP);
	OnMaxXPChanged.Broadcast(MaxXP);
	OnLevelChanged.Broadcast(CurrentLevel);
}


void UXPController::AddXP(float Value)
{
	CurrentXP += Value;
	OnXPChanged.Broadcast(CurrentXP);
	TryLevelUp();
}

// Called when the game starts
void UXPController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UXPController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UXPController::TryLevelUp()
{
	if (CurrentXP >= MaxXP)
	{
		const float XPLeft = CurrentXP - MaxXP;
		CurrentLevel++;
		OnLevelChanged.Broadcast(CurrentLevel);
		MaxXP *= 1.05;
		OnMaxXPChanged.Broadcast(MaxXP);
		CurrentXP = XPLeft;
		
		if (CurrentXP >= MaxXP)
			TryLevelUp();
		
		OnXPChanged.Broadcast(CurrentXP);
	}
}