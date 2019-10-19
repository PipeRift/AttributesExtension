// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Engine/World.h>

#include "AttributesSettings.generated.h"

struct FAttributeReplicationConfig
{
	bool bReplicateBaseValue = true;

	bool bReplicateAttributeModifiers = false;
};


/**
 *
 */
UCLASS(config = Game, defaultconfig)
class ATTRIBUTES_API UAttributesSettings : public UObject
{
	GENERATED_BODY()


private:

	UPROPERTY(config, EditAnywhere, Category = Modifiers, SaveGame)
	TSet<FName> Categories;

	UPROPERTY(config, EditAnywhere, Category = Replication, SaveGame)
	bool bReplicateBaseValue = true;

	UPROPERTY(config, VisibleAnywhere, Category = Replication, SaveGame)
	bool bReplicateAttributeModifiers = false;

	// We keep a global instance of the replication settings for efficiency
	static FAttributeReplicationConfig Replication;

public:

	UAttributesSettings();

	/**
	* @return all categories as a reference
	*/
	const TSet<FName>& GetCategories() const { return Categories; }

protected:

	virtual void BeginDestroy() override;

	void OnWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);

public:

	static const FAttributeReplicationConfig& GetReplication() { return Replication; }
};
