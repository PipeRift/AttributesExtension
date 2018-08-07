// Copyright 2015-2018 Piperift. All Rights Reserved.

#include "FloatAttr.h"
#include "AttributesModule.h"


uint32 FFloatAttr::IdCount{ 0 };


void FFloatAttr::AddModifier(const FAttrModifier& Modifier, const FAttrCategory& Category)
{
	if (Category == FAttrCategory::NoCategory)
	{
		BaseModifiers.Add(Modifier);
	}
	else if(!Category.IsNone())
	{
		int32 Index = CategoryMods.IndexOfByKey(Category);
		if (Index == INDEX_NONE)
		{
			// Add category if non existent
			Index = CategoryMods.HeapPush({ Category });
		}

		CategoryMods[Index].Modifiers.Add(Modifier);
	}
	else
	{
		UE_LOG(LogAttributes, Warning, TEXT("Attributes: tried to add a modifier to the unexisting category '%s'"), *Category.Name.ToString());
		return;
	}

	RefreshValue();
	OnModified.ExecuteIfBound(EAttributeOperation::AO_Add, Modifier);
}

void FFloatAttr::RemoveModifier(const FAttrModifier& Modifier, const FAttrCategory& Category)
{
	if (Category == FAttrCategory::NoCategory)
	{
		BaseModifiers.Remove(Modifier);
	}
	else
	{
		int32 Index = CategoryMods.IndexOfByKey(Category);
		if (Index != INDEX_NONE)
		{
			FAttributeCategoryMods& CategoryMod = CategoryMods[Index];
			CategoryMod.Modifiers.Remove(Modifier);

			if (CategoryMod.Modifiers.Num() <= 0)
			{
				// Remove category if empty
				CategoryMods.HeapRemoveAt(Index);
			}
		}
		else
		{
			UE_LOG(LogAttributes, Warning, TEXT("Attributes: Tried to remove with modifier category '%s', but it doesnt exist on the attribute"), *Category.Name.ToString());
			return;
		}
	}

	RefreshValue();
	OnModified.ExecuteIfBound(EAttributeOperation::AO_Remove, Modifier);
}

const TArray<FAttrModifier>& FFloatAttr::GetModifiers(const FAttrCategory& Category)
{
	int32 Index = CategoryMods.IndexOfByKey(Category);
	if (Index != INDEX_NONE)
	{
		return CategoryMods[Index].Modifiers;
	}
	return BaseModifiers;
}

void FFloatAttr::CleanModifiers()
{
	BaseModifiers.Empty();
	CategoryMods.Empty();
}

void FFloatAttr::RefreshValue()
{
	Value = BaseValue;

	for (auto& Mod : BaseModifiers)
	{
		Mod.Apply(*this, Value);
	}

	for (const auto& Category : CategoryMods)
	{
		for (const auto& Mod : Category.Modifiers)
		{
			Mod.Apply(*this, Value);
		}
	}
}

bool FFloatAttr::ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText)
{
	// Call default import, but skip the native callback to avoid recursion
	Buffer = FFloatAttr::StaticStruct()->ImportText(Buffer, this, Parent, PortFlags, ErrorText, TEXT("FFloatAttr"), false);

	if (Buffer)
	{
		RefreshValue();
	}
	return true;
}
