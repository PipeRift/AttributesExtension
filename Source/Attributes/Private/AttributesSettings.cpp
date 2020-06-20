// Copyright 2015-2020 Piperift. All Rights Reserved.

#include "AttributesSettings.h"
#include "AttributesModule.h"


FAttributeReplicationConfig UAttributesSettings::Replication{};


UAttributesSettings::UAttributesSettings()
	: Super()
{
	Categories.Add(TEXT("Buff"));
	Categories.Add(TEXT("Aura"));

	FWorldDelegates::OnPreWorldInitialization.AddUObject(this, &UAttributesSettings::OnWorldInitialization);
}

void UAttributesSettings::BeginDestroy()
{
	FWorldDelegates::OnPreWorldInitialization.RemoveAll(this);

	Super::BeginDestroy();
}

void UAttributesSettings::OnWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
{
	// Update replication settings
	Replication = { bReplicateBaseValue, bReplicateAttributeModifiers };
}
