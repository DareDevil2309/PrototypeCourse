// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSkill.h"
UTestSkill::UTestSkill()
{
	cooldown = 5.0f;
	skillsComponent = nullptr;
}

void UTestSkill::Cast_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ass")));
	CooldownCut();
}