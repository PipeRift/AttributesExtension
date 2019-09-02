// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "BaseAttr.h"
#include "AttributesModule.h"


uint32 FBaseAttr::IdCount{ 0 };


void FBaseAttr::AddModifier(const FAttrModifier& Modifier, const FAttrCategory& Category)
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
	OnModified.Broadcast(EAttributeOperation::Add, Modifier, Category);
}

bool FBaseAttr::RemoveModifier(const FAttrModifier& Modifier, const FAttrCategory& Category, bool bRemoveFromAllCategories)
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
		OnModified.Broadcast(EAttributeOperation::Remove, Modifier, Category);
	}
	return bChanged;
}

const TArray<FAttrModifier>& FBaseAttr::GetModifiers(const FAttrCategory Category) const
{
	int32 Index = CategoryMods.IndexOfByKey(Category);
	if (Index != INDEX_NONE)
	{
		return CategoryMods[Index].Modifiers;
	}
	return BaseModifiers;
}

void FBaseAttr::GetModifiedCategories(TArray<FAttrCategory>& OutCategories) const
{
	if (BaseModifiers.Num() > 0)
	{
		OutCategories.Reserve(CategoryMods.Num() + 1);
		OutCategories.Add(FAttrCategory::NoCategory);
	}
	else
	{
		OutCategories.Reserve(CategoryMods.Num());
	}

	for (const auto& CategoryMod : CategoryMods)
	{
		OutCategories.Add(CategoryMod.Category);
	}
}

void FBaseAttr::CleanCategoryModifiers(const FAttrCategory& Category)
{
	if (Category.IsNone())
	{
		if (BaseModifiers.Num() > 0)
		{
			BaseModifiers.Empty();

			// Notify
			RefreshValue();
			OnModified.Broadcast(EAttributeOperation::RemoveCategory, {}, Category);
		}
	}
	else
	{
		int32 Index = CategoryMods.IndexOfByKey(Category);
		if (Index != INDEX_NONE)
		{
			// Remove category if empty
			CategoryMods.HeapRemoveAt(Index);

			// Notify
			RefreshValue();
			OnModified.Broadcast(EAttributeOperation::RemoveCategory, {}, Category);
		}
		else
		{
			UE_LOG(LogAttributes, Warning, TEXT("Attributes: Tried to remove all modifiers of category '%s', but it didnt exist on the attribute"), *Category.Name.ToString());
			return;
		}
	}
}

void FBaseAttr::CleanModifiers()
{
	// Is there any modifier at all?
	if (BaseModifiers.Num() > 0 || CategoryMods.Num() > 0)
	{
		BaseModifiers.Empty();
		CategoryMods.Empty();

		RefreshValue();
		OnModified.Broadcast(EAttributeOperation::RemoveAll, {}, FAttrCategory::NoCategory);
	}
}