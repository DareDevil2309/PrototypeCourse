// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MyVerbMessage.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FMyVerbMessage
{
 GENERATED_BODY();
 
 UPROPERTY(BlueprintReadWrite, Category=Gameplay)
 FGameplayTag Verb;
 
 UPROPERTY(BlueprintReadWrite, Category=Gameplay)
 TObjectPtr<UObject> Instigator = nullptr;
 
 UPROPERTY(BlueprintReadWrite, Category=Gameplay)
 TObjectPtr<UObject> Target = nullptr;

 UPROPERTY(BlueprintReadWrite, Category=Gameplay)
 FGameplayTagContainer InstigatorTags;
 
 UPROPERTY(BlueprintReadWrite, Category=Gameplay)
 FGameplayTagContainer TargetTags;

 UPROPERTY(BlueprintReadWrite, Category=Gameplay)
 FGameplayTagContainer ContextTags;
 
 UPROPERTY(BlueprintReadWrite, Category=Gameplay)
 double Magnitude = 1.0;

 FUCK_API FString ToString() const;
};
