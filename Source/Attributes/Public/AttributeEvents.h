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
struct FAttributeChangeInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Change)
	EAttributeOperation Operation;

	UPROPERTY(BlueprintReadOnly, Category = Change)
	FAttrModifier Modifier;

	UPROPERTY(BlueprintReadOnly, Category = Change)
	FAttrCategory Category;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FFloatModifiedDelegate, float, LastValue, const FAttributeChangeInfo&, Modification);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFloatModifiedMCDelegate, float, LastValue, const FAttributeChangeInfo&, Modification);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInt32ModifiedDelegate, int32, LastValue, const FAttributeChangeInfo&, Modification);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInt32ModifiedMCDelegate, int32, LastValue, const FAttributeChangeInfo&, Modification);
