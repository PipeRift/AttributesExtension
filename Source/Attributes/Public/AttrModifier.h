// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include "AttrModifier.generated.h"


struct FFloatAttr;

/* Masks modifier effects in editor. */
UENUM(BlueprintType)
enum class EModifierMask : uint8
{
	Increment,      // X += Value  | Sums a value to the attribute
	LastMultiplier, // X += X * Cof  | Adds the incremental coefficient of the last modified value.
	BaseMultiplier  // X += Base * Cof  | Adds the incremental coefficient of the base value of the attribute.
};


/** Contains modifier values to be applied to an attribute. 32B */
USTRUCT(BlueprintType)
struct ATTRIBUTES_API FAttrModifier
{
	GENERATED_BODY()

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/
protected:

	UPROPERTY(BlueprintReadOnly, Category = Modifier)
	FGuid Guid;

	// We use 4 bytes of alignment for Dirty flags
	UPROPERTY(Transient)
	bool bNetDirty_Guid = true;

public:

	// X += Value  | Sums a value to the attribute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (ColumnWidth = "70", Delta = "0.01"))
	float Increment = 0.f;

	// X += X * Cof  | Adds the incremental coefficient of the last modified value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (ColumnWidth = "70", UIMin = "-1.0", UIMax = "1.0", Delta="0.05", Units = "x"))
	float LastMultiplier = 0.f;

	// X += Base * Cof  | Adds the incremental coefficient of the base value of the attribute.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modifier, meta = (UIMin = "-1.0", UIMax = "1.0", Delta = "0.05", Units = "x"))
	float BaseMultiplier = 0.f;


	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	FAttrModifier() : Guid(FGuid::NewGuid()) {}

	FAttrModifier(EModifierMask Mode, float Value = 0.f);

	FAttrModifier(float Increment, float LastValueMultiplier = 0.f, float BaseValueMultiplier = 0.f);

	FAttrModifier(FAttrModifier&& Other) : Guid(Other.Guid) { SetValues(Other); }
	FAttrModifier(const FAttrModifier& Other) : Guid(Other.Guid) { SetValues(Other); }
	FAttrModifier& operator=(FAttrModifier&& Other)
	{
		Guid = Other.Guid;
		bNetDirty_Guid = true;
		SetValues(Other);
		return *this;
	}
	FAttrModifier& operator=(const FAttrModifier& Other)
	{
		Guid = Other.Guid;
		bNetDirty_Guid = true;
		SetValues(Other);
		return *this;
	}

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
	FORCEINLINE bool operator!=(const FAttrModifier& Other) const { return !(*this == Other); }

	void SetValues(FAttrModifier&& Other)
	{
		Increment = Other.Increment;
		LastMultiplier = Other.LastMultiplier;
		BaseMultiplier = Other.BaseMultiplier;
	}

	void SetValues(const FAttrModifier& Other)
	{
		Increment = Other.Increment;
		LastMultiplier = Other.LastMultiplier;
		BaseMultiplier = Other.BaseMultiplier;
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template<>
struct TStructOpsTypeTraits<FAttrModifier> : public TStructOpsTypeTraitsBase2<FAttrModifier>
{
	enum
	{
		WithCopy = true,
		WithNetSerializer = true,
		WithNetSharedSerialization = true,
		//WithIdenticalViaEquality = true
	};
};


inline bool FAttrModifier::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	// Only replicate non-zero values
	uint8 Flags = (bNetDirty_Guid << 0)
		| (!FMath::IsNearlyZero(Increment)      << 1)
		| (!FMath::IsNearlyZero(LastMultiplier) << 2)
		| (!FMath::IsNearlyZero(BaseMultiplier) << 3);

	Ar.SerializeBits(&Flags, 4);

	bNetDirty_Guid = Flags & 1 << 0;
	if (bNetDirty_Guid)
	{
		Ar << Guid;
		bNetDirty_Guid = false;
	}

	if (Flags & 1 << 1)
		Ar << Increment;
	else
		Increment = 0.f;

	if (Flags & 1 << 2)
		Ar << LastMultiplier;
	else
		LastMultiplier = 0.f;

	if (Flags & 1 << 3)
		Ar << BaseMultiplier;
	else
		BaseMultiplier = 0.f;

	bOutSuccess = true;
	return true;
}
