// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include "AttrModifier.generated.h"

struct FFloatAttr;

/**
 *
 */
USTRUCT(BlueprintType)
struct ATTRIBUTES_API FAttrModifier
{
	GENERATED_BODY()

	FAttrModifier()
		: BasePercentageIncrement(0)
		, PercentageIncrement(0)
		, ScalarIncrement(0)
		, Guid(FGuid::NewGuid())
	{}

	FAttrModifier(float BasePercentageIncrement, float PercentageIncrement = 0, float ScalarIncrement = 0)
		: BasePercentageIncrement(BasePercentageIncrement)
		, PercentageIncrement(PercentageIncrement)
		, ScalarIncrement(ScalarIncrement)
		, Guid(FGuid::NewGuid())
	{}

public:

	UPROPERTY(BlueprintReadOnly, Category = Modifier)
	FGuid Guid;

	/* Adds a percentage of the base value to the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (UIMin = "0.0", UIMax = "100.0"))
	float BasePercentageIncrement;

	/* Adds a percentage of the last value to the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (UIMin = "0.0", UIMax = "100.0"))
	float PercentageIncrement;

	/* Sums an amount to the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier)
	float ScalarIncrement;


	void Apply(const FFloatAttr& Attribute, float& ActualValue) const;


	/** Stack other modifiers values into this mod.
	 * Now applying this modifier will be equivalent to applying all the others at the same time
	 */
	void StackMods(const TArray<FAttrModifier>& OtherMods);

	/** Stack other modifier's values into this mod.
	 * Applying this mod will be equivalent to applying both
	 */
	void StackMod(const FAttrModifier& OtherMod);

	//compare two modifications by guid
	FORCEINLINE bool operator==(const FAttrModifier& Other) const
	{
		return Guid == Other.Guid;
	}
};
