// Copyright 2015-2020 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "BaseAttr.h"
#include "AttrModifier.h"
#include "AttrCategory.h"

#include "DoubleAttr.generated.h"


/**
 * Double Attribute
 * Used as a modular double depending on modifiers
 */
USTRUCT(BlueprintType, meta = (HasNativeBreak = "Attributes.DoubleAttributesLibrary.Break", HasNativeMake = "Attributes.DoubleAttributesLibrary.Make"))
struct ATTRIBUTES_API FDoubleAttr : public FBaseAttr
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute, SaveGame)
	double BaseValue = 0;

	/** Cached final value from modifiers */
	UPROPERTY(EditAnywhere, Category = Attribute, Transient)
	double Value = 0;

	UPROPERTY()
	FDoubleModifiedMCDelegate OnModified;


public:

	FDoubleAttr() : FBaseAttr() {}
	FDoubleAttr(double BaseValue) : FBaseAttr(), BaseValue(BaseValue), Value(BaseValue) {}

	void SetBaseValue(double NewValue);
	double GetBaseValue() const { return BaseValue; }
	double GetValue() const { return Value; }

	/* Get Attribute final value */
	FORCEINLINE operator double() const { return GetValue(); }

	FORCEINLINE double operator+(const double Other) const { return GetValue() + Other; }

	FORCEINLINE double operator-(const double Other) const { return GetValue() - Other; }

	FORCEINLINE double operator+(const FDoubleAttr& Other) const { return *this + Other.GetValue(); }

	FORCEINLINE double operator-(const FDoubleAttr& Other) const { return *this - Other.GetValue(); }

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	void PostSerialize(const FArchive& Ar);
	void PostScriptConstruct();

	FDoubleModifiedMCDelegate& GetOnModified() { return OnModified; }
	const FDoubleModifiedMCDelegate& GetOnModified() const { return OnModified; }

private:

	virtual void InternalRefreshValue(FAttributeChangeInfo&& ChangeInfo) override;
};


template<>
struct TStructOpsTypeTraits<FDoubleAttr> : public TStructOpsTypeTraitsBase2<FDoubleAttr>
{
	enum {
		WithNetSerializer = true,
		WithNetSharedSerialization = true,
		WithPostSerialize = true,
		WithPostScriptConstruct = true
	};
};


inline bool FDoubleAttr::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	if (UAttributesSettings::GetReplication().bReplicateBaseValue)
	{
		Ar << BaseValue;
	}

	Ar << Value;

	bOutSuccess = true;
	return true;
}

inline void FDoubleAttr::PostSerialize(const FArchive& Ar)
{
	// We refresh serialized value for overrided properties or instanced objects
	if(Ar.IsLoading())
	{
		RefreshValue();
	}
}
