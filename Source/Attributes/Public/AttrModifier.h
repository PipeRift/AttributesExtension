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
		: Guid(FGuid::NewGuid())
		, BaseValueMultiplier(0.f)
		, LastValueMultiplier(0.f)
		, Increment(0.f)
	{}

	FAttrModifier(float BaseValueMultiplier, float LastMultiplier = 0.f, float Increment = 0.f)
		: Guid(FGuid::NewGuid())
		, BaseValueMultiplier(BaseValueMultiplier)
		, LastValueMultiplier(LastValueMultiplier)
		, Increment(Increment)
	{}

public:

	UPROPERTY(BlueprintReadOnly, Category = Modifier)
	FGuid Guid;

	/* Adds the incremental coefficient of Base. E.g: +5% damage
	 * X += Base * Cof
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (UIMin = "-1.0", UIMax = "1.0"))
	float BaseValueMultiplier;

	/* Adds the incremental coefficient of the last attribute value. E.g: +5% health
	 * X += X * Cof
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (UIMin = "-1.0", UIMax = "1.0"))
	float LastValueMultiplier;

	/* Sums an amount to the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier)
	float Increment;

	/** Apply changes to the value */
	void Apply(float& Value, float BaseValue) const;

	/** Applies the modifier to the value. This version operates as double to avoid int32 precision lose */
	void Apply(double& Value, int32 BaseValue) const;

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
