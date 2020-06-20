// Copyright 2015-2020 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "BaseAttr.h"
#include "AttrModifier.h"
#include "AttrCategory.h"

#include "Int32Attr.generated.h"


/**
 * Int32 Attribute
 * Used as a modular int32 depending on modifiers
 */
USTRUCT(BlueprintType, meta = (DisplayName="Int32 Attr", HasNativeBreak = "Attributes.Int32AttributesLibrary.Break", HasNativeMake = "Attributes.Int32AttributesLibrary.Make"))
struct ATTRIBUTES_API FInt32Attr : public FBaseAttr
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute, SaveGame)
	int32 BaseValue = 0;

	/** Cached final value from modifiers */
	UPROPERTY(EditAnywhere, Category = Attribute, Transient)
	int32 Value = 0;

	UPROPERTY()
	FInt32ModifiedMCDelegate OnModified;

public:

	FInt32Attr() : FBaseAttr() {}
	FInt32Attr(int32 BaseValue) : FBaseAttr(), BaseValue(BaseValue), Value(BaseValue) {}

	void SetBaseValue(int32 NewValue);
	FORCEINLINE int32 GetBaseValue() const { return BaseValue; }
	FORCEINLINE int32 GetValue() const { return Value; }

	/* Get Attribute final value */
	FORCEINLINE operator int32() const { return GetValue(); }

	FORCEINLINE int32 operator+(const int32 Other) const { return GetValue() + Other; }

	FORCEINLINE int32 operator-(const int32 Other) const { return GetValue() - Other; }

	FORCEINLINE int32 operator+(const FInt32Attr& Other) const { return *this + Other.GetValue(); }

	FORCEINLINE int32 operator-(const FInt32Attr& Other) const { return *this - Other.GetValue(); }

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	void PostSerialize(const FArchive& Ar);
	void PostScriptConstruct();

	FInt32ModifiedMCDelegate& GetOnModified() { return OnModified; }
	const FInt32ModifiedMCDelegate& GetOnModified() const { return OnModified; }

private:

	virtual void InternalRefreshValue(FAttributeChangeInfo&& ChangeInfo) override;
};


template<>
struct TStructOpsTypeTraits<FInt32Attr> : public TStructOpsTypeTraitsBase2<FInt32Attr>
{
	enum {
		WithNetSerializer = true,
		WithNetSharedSerialization = true,
		WithPostSerialize = true,
		WithPostScriptConstruct = true
	};
};


inline bool FInt32Attr::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	if (UAttributesSettings::GetReplication().bReplicateBaseValue)
	{
		Ar << BaseValue;
	}

	Ar << Value;

	bOutSuccess = true;
	return true;
}

inline void FInt32Attr::PostSerialize(const FArchive& Ar)
{
	// We refresh serialized value for overrided properties or instanced objects
	if(Ar.IsLoading())
	{
		RefreshValue();
	}
}
