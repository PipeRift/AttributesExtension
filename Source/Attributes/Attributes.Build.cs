// Copyright 2015-2018 Piperift. All Rights Reserved.

using UnrealBuildTool;

public class Attributes : ModuleRules
{
	public Attributes(ReadOnlyTargetRules TargetRules) : base(TargetRules)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine"
		});
	}
}
