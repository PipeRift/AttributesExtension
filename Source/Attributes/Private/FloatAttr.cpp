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
	OnModified.Broadcast(EAttributeOperation::AO_Add, Modifier, Category);
}

bool FFloatAttr::RemoveModifier(const FAttrModifier& Modifier, const FAttrCategory& Category, bool bRemoveFromAllCategories)
{
	bool bChanged = false;

	if (bRemoveFromAllCategories)
	{
		// Remove possible modifiers from all categories
		bChanged = BaseModifiers.Remove(Modifier) > 0;

		for (int32 CatId = 0; CatId < CategoryMods.Num(); ++CatId)
		{
			FAttributeCategoryMods& CategoryMod = CategoryMods[CatId];

			bChanged = CategoryMod.Modifiers.Remove(Modifier) > 0 || bChanged;

			if (CategoryMod.Modifiers.Num() <= 0)
			{
				// Remove category if empty
				CategoryMods.HeapRemoveAt(CatId);

				//Reduce Id, because current one doesn't exist anymore
				--CatId;
			}
		}
	}
	else if (Category == FAttrCategory::NoCategory)
	{
		// Remove modifier from base modifiers
		bChanged = BaseModifiers.Remove(Modifier) > 0;
	}
	else
	{
		// Remove modifier from a category
		int32 Index = CategoryMods.IndexOfByKey(Category);
		if (Index != INDEX_NONE)
		{
			FAttributeCategoryMods& CategoryMod = CategoryMods[Index];
			bChanged = CategoryMod.Modifiers.Remove(Modifier) > 0;

			if (CategoryMod.Modifiers.Num() <= 0)
			{
				// Remove category if empty
				CategoryMods.HeapRemoveAt(Index);
			}
		}
		else
		{
			UE_LOG(LogAttributes, Warning, TEXT("Attributes: Tried to remove with modifier category '%s', but it doesnt exist on the attribute"), *Category.Name.ToString());
			return false;
		}
	}

	if (bChanged)
	{
		RefreshValue();
		OnModified.Broadcast(EAttributeOperation::AO_Remove, Modifier, Category);
	}
	return bChanged;
}

const TArray<FAttrModifier>& FFloatAttr::GetModifiers(const FAttrCategory& Category) const
{
	int32 Index = CategoryMods.IndexOfByKey(Category);
	if (Index != INDEX_NONE)
	{
		return CategoryMods[Index].Modifiers;
	}
	return BaseModifiers;
}

void FFloatAttr::CleanCategoryModifiers(const FAttrCategory& Category)
{
	if (Category.IsNone())
	{
		BaseModifiers.Empty();
	}
	else
	{
		int32 Index = CategoryMods.IndexOfByKey(Category);
		if (Index != INDEX_NONE)
		{
			// Remove category if empty
			CategoryMods.HeapRemoveAt(Index);
		}
		else
		{
			UE_LOG(LogAttributes, Warning, TEXT("Attributes: Tried to remove all modifiers of category '%s', but it didnt exist on the attribute"), *Category.Name.ToString());
			return;
		}
	}

	RefreshValue();
	OnModified.Broadcast(EAttributeOperation::AO_RemoveCategory, {}, Category);
}

void FFloatAttr::CleanModifiers()
{
	BaseModifiers.Empty();
	CategoryMods.Empty();

	RefreshValue();
	OnModified.Broadcast(EAttributeOperation::AO_RemoveAll, {}, FAttrCategory::NoCategory);
}

void FFloatAttr::RefreshValue()
{
	Value = BaseValue;

	for (const auto& Mod : BaseModifiers)
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

void FFloatAttr::SetBaseValue(float NewValue)
{
	if (NewValue != BaseValue)
	{
		BaseValue = NewValue;

		RefreshValue();
		OnModified.Broadcast(EAttributeOperation::AO_Base, {}, FAttrCategory::NoCategory);
	}
}

void FFloatAttr::PostSerialize(const FArchive & Ar)
{
	if (Ar.IsSaving())
		RefreshValue();
}
