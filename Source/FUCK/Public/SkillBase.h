// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FUCK/PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "SkillBase.generated.h"

class USkillsComponent;


UCLASS(Blueprintable)
class FUCK_API USkillBase : public UObject
{
	GENERATED_BODY()
	
public:
	USkillBase();

	//Держит реализацию кулдауна
	virtual void Initialize();

	UPROPERTY(EditAnywhere)
	float cooldown;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Cast();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCooldown();

	//Заменить это для новых C++ классов
	virtual void Cast_Implementation();

	UFUNCTION(BlueprintCallable)
	void CooldownCut(float cut = 0.f);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly,meta = (EditConditionHides))
	USkillsComponent* skillsComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (EditConditionHides))
	APlayerCharacter* player;

	float cooldownTimestamp;

protected:

private:

};

