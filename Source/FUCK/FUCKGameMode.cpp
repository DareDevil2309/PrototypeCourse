// Copyright Epic Games, Inc. All Rights Reserved.

#include "FUCKGameMode.h"
#include "FUCKCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFUCKGameMode::AFUCKGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
