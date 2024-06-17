// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class FUCK_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init();

	UFUNCTION(BlueprintCallable)
	void Resume();

	UFUNCTION(BlueprintCallable)
	void ShowOptions();

	UFUNCTION(BlueprintCallable)
	void Exit();

	UFUNCTION(BlueprintCallable)
	void Save();

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenuMap;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionsButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;
};
