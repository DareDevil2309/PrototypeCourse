// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FUCK : ModuleRules
{
	public FUCK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "UMG", "UIFramework", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayCameras", "HeadMountedDisplay", "Niagara" });
        PrivateDependencyModuleNames.AddRange(new string[] {"Slate", "SlateCore" });
    }
}
