// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <FUCK/PlayerCharacter.h>
#include "SkillBase.h"
#include <FUCK/Skills/TestSkill.h>
#include "SkillsComponent.generated.h"





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUCK_API USkillsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillsComponent();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<USkillBase>> skillsClass;

	UPROPERTY()
	TArray <USkillBase*> skillsObject;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SkillOne();
	void SkillTwo();
	void SkillThree();
	void SkillFour();
	void Skill(int index);

		
};
