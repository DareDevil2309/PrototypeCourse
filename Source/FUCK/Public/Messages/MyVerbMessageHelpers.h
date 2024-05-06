// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "MyVerbMessage.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyVerbMessageHelpers.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UMyVerbMessageHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Lyra")
	static APlayerState* GetPlayerStateFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Lyra")
	static APlayerController* GetPlayerControllerFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Lyra")
	static FGameplayCueParameters VerbMessageToCueParameters(const FMyVerbMessage& Message);

	UFUNCTION(BlueprintCallable, Category = "Lyra")
	static FMyVerbMessage CueParametersToVerbMessage(const FGameplayCueParameters& Params);
};
