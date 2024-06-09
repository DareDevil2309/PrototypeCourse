// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "UObject/Object.h"
#include "WidgetsController.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UWidgetsController : public UObject
{
	GENERATED_BODY()
public:
	UWidgetsController();
	TArray<TObjectPtr<UWidget>>*  Widgets;
};
