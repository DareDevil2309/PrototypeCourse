// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillsComponent.h"

// Sets default values for this component's properties
USkillsComponent::USkillsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


// Called when the game starts
void USkillsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	this->GetOwner()->InputComponent->BindAction(FName("Skill1"), IE_Pressed, this, &USkillsComponent::SkillOne);
	this->GetOwner()->InputComponent->BindAction(FName("Skill2"), IE_Pressed, this, &USkillsComponent::SkillTwo);
	this->GetOwner()->InputComponent->BindAction(FName("Skill3"), IE_Pressed, this, &USkillsComponent::SkillThree);
	this->GetOwner()->InputComponent->BindAction(FName("Skill4"), IE_Pressed, this, &USkillsComponent::SkillFour);
	
	for (int32 i = 0; i < skillsClass.Num(); i++)
	{
		if (skillsClass[i])
		{
			skillsObject.Add(NewObject<USkillBase>(this->GetOwner(), skillsClass[i]));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, skillsClass[i]->GetName());
		}

		if (skillsObject[i])
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Skill object %d initialized"), i));
			skillsObject[i]->cooldownTimestamp = 1.f;
			skillsObject[i]->skillsComponent = this;
			skillsObject[i]->player = Cast<APlayerCharacter>(GetOwner());
		}
	}
}

// Called every frame
void USkillsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillsComponent::SkillOne()
{
	if (skillsObject.IsValidIndex(0))
		if(skillsObject[0])
		{
			skillsObject[0]->Initialize();
		}


}

void USkillsComponent::SkillTwo()
{
	if (skillsObject.IsValidIndex(1))
		if (skillsObject[1]) 
		{
			skillsObject[1]->Initialize();
		}
}

void USkillsComponent::SkillThree()
{
	if (skillsObject.IsValidIndex(2))
		if (skillsObject[2]) 
		{
			skillsObject[2]->Initialize();
		}
}

void USkillsComponent::SkillFour()
{
	if (skillsObject.IsValidIndex(3))
		if (skillsObject[3]) 
		{
			skillsObject[3]->Initialize();
		}
}

void USkillsComponent::Skill(int index)
{
	if (skillsObject.IsValidIndex(index))
		if (skillsObject[index])
		{
			skillsObject[index]->Initialize();
		}
}
