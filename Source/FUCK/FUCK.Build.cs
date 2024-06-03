// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FUCK : ModuleRules
{
	public FUCK(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayMessageRuntime", "GameplayMessageRuntime" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core",
	        "CoreUObject",
	        "Engine",
	        "InputCore",
	        "EnhancedInput",
	        "AIModule",
	        "GameplayCameras",
	        "HeadMountedDisplay",
	        "GameplayAbilities",
	        "GameplayTags",
	        "GameplayTasks",
	        
	        "ApplicationCore",
	        "PhysicsCore",
	        "AIModule",
	        "DataRegistry",
	        "ReplicationGraph",
	        "GameFeatures",
	        "SignificanceManager",
	        "Hotfix",
	        "Niagara",
	        "ControlFlows",
	        "PropertyPath",
	        "GameplayMessageRuntime"
        });
    }
}
