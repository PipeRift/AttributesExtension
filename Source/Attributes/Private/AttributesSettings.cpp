// Copyright 2015-2018 Piperift. All Rights Reserved.

#include "AttributesSettings.h"
#include "AttributesModule.h"


UAttributesSettings::UAttributesSettings()
	: Super()
{
	Categories.Add(TEXT("Buff"));
	Categories.Add(TEXT("Aura"));

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UAttributesSettings::OnWorldInitialization);
}

void UAttributesSettings::BeginDestroy()
{
	FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);

	Super::BeginDestroy();
}

void UAttributesSettings::OnWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
{
	//Initialize manager
	//FAttributesModule::GetAttributesManager();
}
