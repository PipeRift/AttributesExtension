// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "AttrModifier.h"
#include "AttrCategory.h"

#include "AttributeEvents.generated.h"


UENUM(BlueprintType)
enum class EAttributeOperation : uint8
{
	None UMETA(Hidden),
	BaseValueChanged,
	AddedMod,
	RemovedMod,
	RemovedAllMods,
	RemovedCategory
};


USTRUCT(BlueprintType)
struct FAttributeModifiedInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EAttributeOperation Operation;

	UPROPERTY(BlueprintReadOnly)
	FAttrModifier Modifier;

	UPROPERTY(BlueprintReadOnly)
	FAttrCategory Category;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatModifiedDelegate, float, LastValue, const FAttributeModifiedInfo&, Modification);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFloatModifiedMCDelegate, float, LastValue, const FAttributeModifiedInfo&, Modification);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInt32ModifiedDelegate, int32, LastValue, const FAttributeModifiedInfo&, Modification);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInt32ModifiedMCDelegate, int32, LastValue, const FAttributeModifiedInfo&, Modification);
