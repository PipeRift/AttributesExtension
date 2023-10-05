// Copyright 2015-2020 Piperift. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class AttributesTest : ModuleRules
	{
		public AttributesTest(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
			IWYUSupport = IWYUSupport.Full;

			PublicDependencyModuleNames.AddRange(new string[]
			{
				"Core",
				"Engine",
				"CoreUObject",
				"Attributes"
			});

			PrivateDependencyModuleNames.AddRange(new string[]
			{
			});
		}
	}
}