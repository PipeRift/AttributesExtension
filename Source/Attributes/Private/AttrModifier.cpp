// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "AttrModifier.h"
#include "FloatAttr.h"


FAttrModifier::FAttrModifier(EModifierMask Mode, float Value)
	: Guid(FGuid::NewGuid())
{
	switch (Mode)
	{
	case EModifierMask::Increment:
		Increment = Value;
		break;
	case EModifierMask::LastMultiplier:
		LastMultiplier = Value;
		break;
	case EModifierMask::BaseMultiplier:
		BaseMultiplier = Value;
		break;
	}
}

FAttrModifier::FAttrModifier(float Increment, float LastValueMultiplier, float BaseValueMultiplier)
	: Guid(FGuid::NewGuid())
	, Increment(Increment)
	, LastMultiplier(LastValueMultiplier)
	, BaseMultiplier(BaseValueMultiplier)
{
}

void FAttrModifier::Apply(float& Value, float BaseValue) const
{
	if (!FMath::IsNearlyZero(LastMultiplier))
	{
		Value *= 1.0f + LastMultiplier;
	}
	if (!FMath::IsNearlyZero(BaseMultiplier))
	{
		Value += BaseMultiplier * BaseValue;
	}
	Value += Increment;
}

void FAttrModifier::Apply(double& Value, int32 BaseValue) const
{
	if (!FMath::IsNearlyZero(LastMultiplier))
	{
		Value *= 1.0 + LastMultiplier;
	}
	if (!FMath::IsNearlyZero(BaseMultiplier))
	{
		Value += BaseMultiplier * BaseValue;
	}
	Value += Increment;
}

void FAttrModifier::StackMods(const TArray<FAttrModifier>& OtherMods)
{
	for (const auto& Mod : OtherMods)
	{
		StackMod(Mod);
	}
}

void FAttrModifier::StackMod(const FAttrModifier& OtherMod)
{
	if (!FMath::IsNearlyZero(OtherMod.LastMultiplier))
	{
		// Stack % value
		LastMultiplier = (1.f + LastMultiplier) * (1.f + OtherMod.LastMultiplier) - 1.0f;
	}
	if (!FMath::IsNearlyZero(OtherMod.BaseMultiplier))
	{
		// Stack % base value
		BaseMultiplier = (1.f + BaseMultiplier) * (1.f + OtherMod.BaseMultiplier) - 1.0f;
	}
	Increment += OtherMod.Increment;
}
