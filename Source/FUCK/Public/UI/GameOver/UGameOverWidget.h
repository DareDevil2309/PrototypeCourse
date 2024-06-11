// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init();
	UFUNCTION(BlueprintImplementableEvent)
	void Inited();

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenuMap;
};
