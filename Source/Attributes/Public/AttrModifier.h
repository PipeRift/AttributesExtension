// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
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
		, Increment(0.f)
		, LastValueMultiplier(0.f)
		, BaseValueMultiplier(0.f)
	{}

	FAttrModifier(float BaseValueMultiplier, float LastValueMultiplier = 0.f, float Increment = 0.f)
		: Guid(FGuid::NewGuid())
		, Increment(Increment)
		, LastValueMultiplier(LastValueMultiplier)
		, BaseValueMultiplier(BaseValueMultiplier)
	{}

public:

	UPROPERTY(BlueprintReadOnly, Category = Modifier)
	FGuid Guid;

	/* Sums an amount to the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier)
	float Increment;

	/* Adds the incremental coefficient of the last attribute value. E.g: +5% health
	 * X += X * Cof
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (UIMin = "-1.0", UIMax = "1.0"))
	float LastValueMultiplier;

	/* Adds the incremental coefficient of Base. E.g: +5% damage
	 * X += Base * Cof
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (UIMin = "-1.0", UIMax = "1.0"))
	float BaseValueMultiplier;


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
