// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace MyGameplayTags
{
	FUCK_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);
	FUCK_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_GodMode);
	FUCK_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_UnlimitedHealth);
}