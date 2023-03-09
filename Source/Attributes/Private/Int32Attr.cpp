// Copyright 2015-2020 Piperift. All Rights Reserved.

#include "Int32Attr.h"
#include "AttributesModule.h"


void FInt32Attr::SetBaseValue(int32 NewValue)
{
	if (NewValue != BaseValue)
	{
		BaseValue = NewValue;

		// Notify
		InternalRefreshValue({
			EAttributeOperation::BaseValueChanged,
			{},
			FAttrCategory::NoCategory
		});
	}
}

void FInt32Attr::PostScriptConstruct()
{
	RefreshValue();
}

void FInt32Attr::InternalRefreshValue(FAttributeChangeInfo&& ChangeInfo)
{
	const int32 LastValue = Value;
	double TempValue = BaseValue;

	for (const auto& Mod : BaseModifiers)
	{
		Mod.Apply(TempValue, BaseValue);
	}

	for (const auto& Category : CategoryMods)
	{
		for (const auto& Mod : Category.Modifiers)
		{
			Mod.Apply(TempValue, double(BaseValue));
		}
	}

	Value = FMath::RoundToInt(TempValue);

	// Notify changes
	OnModified.Broadcast(LastValue, ChangeInfo);
}
