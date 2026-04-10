// Copyright 2015-2026 Piperift. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class AttributesTest : ModuleRules
	{
		public AttributesTest(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(new string[]
			{
				"Core"
			});

			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"Attributes",
				"CoreUObject",
				"Engine",
				"EngineSettings"
			});

			if (Target.bBuildEditor == true)
			{
				PrivateDependencyModuleNames.Add("UnrealEd");
			}
		}
	}
}