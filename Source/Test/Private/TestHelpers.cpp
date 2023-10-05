// Copyright 2015-2023 Piperift. All Rights Reserved.

#include "TestHelpers.h"

#include <Engine/Engine.h>
#include <Engine/LocalPlayer.h>
#include <EngineUtils.h>
#include <GameFramework/Actor.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/WorldSettings.h>



UWorld* FAESpec::GetTestWorld() const
{
#if WITH_EDITOR
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts)
	{
		if (Context.World() != nullptr)
		{
			if (Context.WorldType == EWorldType::PIE /*&& Context.PIEInstance == 0*/)
			{
				return Context.World();
			}

			if (Context.WorldType == EWorldType::Game)
			{
				return Context.World();
			}
		}
	}
#endif

	UWorld* TestWorld = GWorld;
	if (GIsEditor)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttributesExtension Test using GWorld. Not correct for PIE"));
	}

	return TestWorld;
}
