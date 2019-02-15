// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "AttrModifier.h"
#include "FloatAttr.h"


void FAttrModifier::Apply(const FFloatAttr& Attribute, float& ActualValue) const {
	if (!FMath::IsNearlyZero(PercentageIncrement)) {
		ActualValue *= 1.f + (PercentageIncrement * 0.01f);
	}

	if (!FMath::IsNearlyZero(BasePercentageIncrement)) {
		ActualValue += Attribute.GetBaseValue() * (BasePercentageIncrement * 0.01f);
	}

	ActualValue += ScalarIncrement;
}

void FAttrModifier::StackMods(const TArray<FAttrModifier>& OtherMods)
{
}

void FAttrModifier::StackMod(const FAttrModifier& OtherMod)
{
	if (!FMath::IsNearlyZero(OtherMod.PercentageIncrement)) {
		// Stack % value
		PercentageIncrement = ((1.f + PercentageIncrement * 0.01f) * (1.f + OtherMod.PercentageIncrement * 0.01f) - 1) * 100.f;
	}

	if (!FMath::IsNearlyZero(OtherMod.BasePercentageIncrement)) {
		// Stack % base value
		BasePercentageIncrement = ((1.f + BasePercentageIncrement * 0.01f) * (1.f + OtherMod.BasePercentageIncrement * 0.01f) - 1) * 100.f;
	}

	ScalarIncrement += OtherMod.ScalarIncrement;
}
