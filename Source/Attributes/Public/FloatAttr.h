// Copyright 2015-2023 Piperift. All Rights Reserved.

#pragma once

#include "AttrCategory.h"
#include "AttrModifier.h"
#include "BaseAttr.h"

#include <CoreMinimal.h>

#include "FloatAttr.generated.h"


/**
 * Float Attribute
 * Used as a modular float depending on modifiers
 */
USTRUCT(BlueprintType, meta = (HasNativeBreak = "Attributes.FloatAttributesLibrary.Break",
						   HasNativeMake = "Attributes.FloatAttributesLibrary.Make"))
struct ATTRIBUTES_API FFloatAttr : public FBaseAttr
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute, SaveGame)
	float BaseValue = 0.f;

	/** Cached final value from modifiers */
	UPROPERTY(EditAnywhere, Category = Attribute, Transient)
	float Value = 0.f;

	UPROPERTY()
	FFloatModifiedMCDelegate OnModified;


public:
	FFloatAttr() : FBaseAttr() {}
	FFloatAttr(float BaseValue) : FBaseAttr(), BaseValue(BaseValue), Value(BaseValue) {}

	void SetBaseValue(float NewValue);
	float GetBaseValue() const
	{
		return BaseValue;
	}
	float GetValue() const
	{
		return Value;
	}

	/* Get Attribute final value */
	FORCEINLINE operator float() const
	{
		return GetValue();
	}

	FORCEINLINE float operator+(const float Other) const
	{
		return GetValue() + Other;
	}

	FORCEINLINE float operator-(const float Other) const
	{
		return GetValue() - Other;
	}

	FORCEINLINE float operator+(const FFloatAttr& Other) const
	{
		return *this + Other.GetValue();
	}

	FORCEINLINE float operator-(const FFloatAttr& Other) const
	{
		return *this - Other.GetValue();
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	void PostSerialize(const FArchive& Ar);
	void PostScriptConstruct();

	FFloatModifiedMCDelegate& GetOnModified()
	{
		return OnModified;
	}
	const FFloatModifiedMCDelegate& GetOnModified() const
	{
		return OnModified;
	}

private:
	virtual void InternalRefreshValue(FAttributeChangeInfo&& ChangeInfo) override;
};


template <>
struct TStructOpsTypeTraits<FFloatAttr> : public TStructOpsTypeTraitsBase2<FFloatAttr>
{
	enum
	{
		WithNetSerializer = true,
		WithNetSharedSerialization = true,
		WithPostSerialize = true,
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

inline void FFloatAttr::PostSerialize(const FArchive& Ar)
{
	// We refresh serialized value for overrided properties or instanced objects
	if (Ar.IsLoading())
	{
		RefreshValue();
	}
}
