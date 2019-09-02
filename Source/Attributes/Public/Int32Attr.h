// Copyright 2015-2019 Piperift. All Rights Reserved.

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
USTRUCT(BlueprintType, meta = (HiddenByDefault))
struct ATTRIBUTES_API FInt32Attr : public FBaseAttr
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute, SaveGame)
	int32 BaseValue;

private:

	/** Cached final value from modifiers */
	UPROPERTY()
	int32 Value;


public:

	FInt32Attr(int32 BaseValue = 0)
		: FBaseAttr()
		, BaseValue(BaseValue)
		, Value(BaseValue)
	{}

	void SetBaseValue(int32 NewValue);
	FORCEINLINE int32 GetBaseValue() const { return BaseValue; }
	FORCEINLINE int32 GetValue() const { return Value; }

	/* Get Attribute final value */
	FORCEINLINE operator int32() const { return GetValue(); }

	FORCEINLINE int32 operator+(const int32 Other) const { return GetValue() + Other; }

	FORCEINLINE int32 operator-(const int32 Other) const { return GetValue() - Other; }

	FORCEINLINE int32 operator+(const FInt32Attr& Other) const { return *this + Other.GetValue(); }

	FORCEINLINE int32 operator-(const FInt32Attr& Other) const { return *this - Other.GetValue(); }

	void PostSerialize(const FArchive& Ar);

private:

	virtual void RefreshValue() override;
};

template<>
struct TStructOpsTypeTraits<FInt32Attr> : public TStructOpsTypeTraitsBase2<FInt32Attr>
{
	enum
	{
		WithPostSerialize = true
	};
};
