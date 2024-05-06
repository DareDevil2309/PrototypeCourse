// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Abilities/MyAttributeSet.h"

UMyAttributeSet::UMyAttributeSet()
{
	
}

UWorld* UMyAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);
	return Outer->GetWorld();
}
