// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "TestSkill.generated.h"

class USkillsComponent;
/**
 * 
 */
UCLASS()
class FUCK_API UTestSkill : public USkillBase
{
	GENERATED_BODY()
	
public:
	UTestSkill();

	void Cast_Implementation() override;

};
