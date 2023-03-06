// Copyright 2015-2020 Piperift. All Rights Reserved.

#include "DoubleAttr.h"
#include "AttributesModule.h"


void FDoubleAttr::SetBaseValue(double NewValue)
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

void FDoubleAttr::PostScriptConstruct()
{
	RefreshValue();
}

void FDoubleAttr::InternalRefreshValue(FAttributeChangeInfo&& ChangeInfo)
{
	const double LastValue = Value;
	Value = BaseValue;

	for (const auto& Mod : BaseModifiers)
	{
		Mod.Apply(Value, BaseValue);
	}

	for (const auto& Category : CategoryMods)
	{
		for (const auto& Mod : Category.Modifiers)
		{
			Mod.Apply(Value, BaseValue);
		}
	}

	// Notify changes
	OnModified.Broadcast(LastValue, ChangeInfo);
}