// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "BaseAttr.h"
#include "AttrModifier.h"
#include "AttrCategory.h"

#include "FloatAttr.generated.h"


/**
 * Float Attribute
 * Used as a modular float depending on modifiers
 */
USTRUCT(BlueprintType, meta = (HasNativeBreak = "Attributes.FloatAttributesLibrary.Break", HasNativeMake = "Attributes.FloatAttributesLibrary.Make"))
struct ATTRIBUTES_API FFloatAttr : public FBaseAttr
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute, SaveGame)
	float BaseValue = 0.f;

	/** Cached final value from modifiers */
	UPROPERTY(EditAnywhere, Category = Attribute, Transient)
	float Value = 0.f;


public:

	FFloatAttr() : FBaseAttr() {}
	FFloatAttr(float BaseValue) : FBaseAttr(), BaseValue(BaseValue), Value(BaseValue) {}

	void SetBaseValue(float NewValue);
	float GetBaseValue() const { return BaseValue; }
	float GetValue() const { return Value; }

	/* Get Attribute final value */
	FORCEINLINE operator float() const { return GetValue(); }

	FORCEINLINE float operator+(const float Other) const { return GetValue() + Other; }

	FORCEINLINE float operator-(const float Other) const { return GetValue() - Other; }

	FORCEINLINE float operator+(const FFloatAttr& Other) const { return *this + Other.GetValue(); }

	FORCEINLINE float operator-(const FFloatAttr& Other) const { return *this - Other.GetValue(); }

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	void PostScriptConstruct();

private:

	virtual void RefreshValue() override;
};


template<>
struct TStructOpsTypeTraits<FFloatAttr> : public TStructOpsTypeTraitsBase2<FFloatAttr>
{
	enum {
		WithNetSerializer = true,
		WithNetSharedSerialization = true,
		WithPostScriptConstruct = true
	};
};


inline bool FFloatAttr::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	if (UAttributesSettings::GetReplication().bReplicateBaseValue)
	{
		Ar << BaseValue;
	}

	Ar << Value;

	bOutSuccess = true;
	return true;
}
