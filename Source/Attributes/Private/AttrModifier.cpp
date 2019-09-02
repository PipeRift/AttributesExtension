// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "AttrModifier.h"
#include "FloatAttr.h"


void FAttrModifier::Apply(float& Value, float BaseValue) const
{
	if (!FMath::IsNearlyZero(LastValueMultiplier))
	{
		Value *= 1.0f + LastValueMultiplier;
	}
	if (!FMath::IsNearlyZero(BaseValueMultiplier))
	{
		Value += BaseValueMultiplier * BaseValue;
	}
	Value += Increment;
}

void FAttrModifier::Apply(double& Value, int32 BaseValue) const
{
	if (!FMath::IsNearlyZero(LastValueMultiplier))
	{
		Value *= 1.0 + LastValueMultiplier;
	}
	if (!FMath::IsNearlyZero(BaseValueMultiplier))
	{
		Value += BaseValueMultiplier * BaseValue;
	}
	Value += Increment;
}

void FAttrModifier::StackMods(const TArray<FAttrModifier>& OtherMods)
{
}

void FAttrModifier::StackMod(const FAttrModifier& OtherMod)
{
	if (!FMath::IsNearlyZero(OtherMod.LastValueMultiplier))
	{
		// Stack % value
		LastValueMultiplier = (1.f + LastValueMultiplier) * (1.f + OtherMod.LastValueMultiplier) - 1.0f;
	}
	if (!FMath::IsNearlyZero(OtherMod.BaseValueMultiplier))
	{
		// Stack % base value
		BaseValueMultiplier = (1.f + BaseValueMultiplier) * (1.f + OtherMod.BaseValueMultiplier) - 1.0f;
	}
	Increment += OtherMod.Increment;
}
