// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"


USkillBase::USkillBase()
{
	cooldownTimestamp = 0.f;
	cooldown = 0.f;
}

void USkillBase::Initialize()
{
	if (UGameplayStatics::GetTimeSeconds(GetWorld()) >= cooldownTimestamp)
	{			
		cooldownTimestamp = UGameplayStatics::GetTimeSeconds(GetWorld()) + cooldown;
		Cast();
	}
}

void USkillBase::Cast_Implementation()
{
	
}

void USkillBase::CooldownCut(float cut)
{
	if (cut != 0.f)
	{
		cooldownTimestamp += -cut;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(cooldownTimestamp));

	}
	else
	{
		cooldownTimestamp = 0.0f;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(cooldownTimestamp));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(UGameplayStatics::GetTimeSeconds(GetWorld())));
	}
}

float USkillBase::GetCooldown()
{
	return  FMath::Clamp(cooldownTimestamp - UGameplayStatics::GetTimeSeconds(GetWorld()), 0, INFINITY);
}
