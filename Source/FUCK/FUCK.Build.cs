// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FUCK : ModuleRules
{
	public FUCK(ReadOnlyTargetRules Target) : base(Target)
	{
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
	        "PropertyPath"
        });
        
        PrivateDependencyModuleNames.AddRange(new string[]
        {
	        "GameplayMessageRuntime",
	        "InputCore",
	        "Slate",
	        "SlateCore",
	        "RenderCore",
	        "DeveloperSettings",
	        "EnhancedInput",
	        "NetCore",
	        "RHI",
	        "Projects",
	        "Gauntlet",
	        "UMG",
	        "CommonUI",
	        "CommonInput",
	        "AudioMixer",
	        "NetworkReplayStreaming",
	        "ClientPilot",
	        "AudioModulation",
	        "EngineSettings",
	        "DTLSHandlerComponent",
        });
    }
}
