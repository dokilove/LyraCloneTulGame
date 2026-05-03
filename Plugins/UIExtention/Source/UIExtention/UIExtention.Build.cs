// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UIExtention : ModuleRules
{
	public UIExtention(ReadOnlyTargetRules Target) : base(Target)
	{		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"SlateCore",
				"Slate",
				"UMG",
				"CommonUI",
				"CommonGame",
				"GameplayTags"
			}
			);

		PublicIncludePathModuleNames.AddRange(
			new string[] {
			}
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
