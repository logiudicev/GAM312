// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM312 : ModuleRules
{
	public GAM312(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		//add UI Elements UMG, Slate and SlateCore
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
			"HeadMountedDisplay", "UMG", "Slate", "SlateCore" });
	}
}
