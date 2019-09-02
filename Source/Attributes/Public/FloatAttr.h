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
USTRUCT(BlueprintType, meta = (HiddenByDefault))
struct ATTRIBUTES_API FFloatAttr : public FBaseAttr
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute, SaveGame)
	float BaseValue;

private:

	/** Cached final value from modifiers */
	UPROPERTY()
	float Value;


public:

	FFloatAttr(float BaseValue = 0.f)
		: FBaseAttr()
		, BaseValue(BaseValue)
		, Value(BaseValue)
	{}

	void SetBaseValue(float NewValue);
	float GetBaseValue() const { return BaseValue; }
	float GetValue() const { return Value; }


	/* Get Attribute final value */
	FORCEINLINE operator float() const { return GetValue(); }

	FORCEINLINE float operator+(const float Other) const { return GetValue() + Other; }

	FORCEINLINE float operator-(const float Other) const { return GetValue() - Other; }

	FORCEINLINE float operator+(const FFloatAttr& Other) const { return *this + Other.GetValue(); }

	FORCEINLINE float operator-(const FFloatAttr& Other) const { return *this - Other.GetValue(); }

	void PostSerialize(const FArchive& Ar);

private:

	virtual void RefreshValue() override;
};

template<>
struct TStructOpsTypeTraits<FFloatAttr> : public TStructOpsTypeTraitsBase2<FFloatAttr>
{
	enum
	{
		WithPostSerialize = true
	};
};
