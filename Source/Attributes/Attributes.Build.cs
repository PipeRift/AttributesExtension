// Copyright 2015-2018 Piperift. All Rights Reserved.

using UnrealBuildTool;

public class Attributes : ModuleRules
{
	public Attributes(ReadOnlyTargetRules TargetRules) : base(TargetRules)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {
			"Attributes/Public"
			// ... add public include paths required here ...
		});


		PrivateIncludePaths.AddRange(new string[] {
			"Attributes/Private"
			// ... add other private include paths required here ...
		});


		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine"
			// ... add other public dependencies that you statically link with here ...
		});


		PrivateDependencyModuleNames.AddRange(new string[] {
			// ... add private dependencies that you statically link with here ...
		});


		DynamicallyLoadedModuleNames.AddRange(new string[] {
			// ... add any modules that your module loads dynamically here ...
		});
	}
}
