// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FUCK : ModuleRules
{
	public FUCK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayCameras", "HeadMountedDisplay" });
    }
}
