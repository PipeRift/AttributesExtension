// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "Int32Attr.h"
#include "AttributesModule.h"


void FInt32Attr::SetBaseValue(int32 NewValue)
{
	if (NewValue != BaseValue)
	{
		BaseValue = NewValue;

		// Notify
		RefreshValue();
		OnModified.Broadcast(EAttributeOperation::Base, {}, FAttrCategory::NoCategory);
	}
}

void FInt32Attr::PostSerialize(const FArchive & Ar)
{
	if (Ar.IsSaving())
	{
		RefreshValue();
	}
}

void FInt32Attr::RefreshValue()
{
	double TempValue = BaseValue;

	for (const auto& Mod : BaseModifiers)
	{
		Mod.Apply(TempValue, BaseValue);
	}

	for (const auto& Category : CategoryMods)
	{
		for (const auto& Mod : Category.Modifiers)
		{
			Mod.Apply(TempValue, BaseValue);
		}
	}

	Value = FMath::RoundToInt(TempValue);
}
