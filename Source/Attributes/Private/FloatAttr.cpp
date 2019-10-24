// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "FloatAttr.h"
#include "AttributesModule.h"


void FFloatAttr::SetBaseValue(float NewValue)
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

void FFloatAttr::PostScriptConstruct()
{
	RefreshValue();
}

void FFloatAttr::InternalRefreshValue(FAttributeModifiedInfo&& ChangeInfo)
{
	const float LastValue = Value;
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