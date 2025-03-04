// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RM : ModuleRules
{
	public RM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] 
		{ "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" 
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayTags", "GameplayTasks", "GameplayAbilities"
		});
	}
}
