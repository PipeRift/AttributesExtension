// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Engine/World.h>

#include "AttributesSettings.generated.h"


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


public:

	UAttributesSettings();

	/**
	* @return all categories as a reference
	*/
	const TSet<FName>& GetCategories() const { return Categories; }

protected:

	virtual void BeginDestroy() override;

	void OnWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);
};
