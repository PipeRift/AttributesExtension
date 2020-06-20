// Copyright 2015-2020 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "AttrModifier.h"
#include "AttrCategory.h"
#include "AttributeEvents.h"

#include "BaseAttr.generated.h"


/**
 * Base Attribute
 * Extended upon to support different types of attributes
 */
USTRUCT()
struct ATTRIBUTES_API FBaseAttr
{
	GENERATED_BODY()

private:

	/** Using an static counter for Ids.
	 * Reduces Id from 16 to 4 bytes.
	 * If you need more, change ids to 64
	 */
	static uint32 IdCount;

	UPROPERTY(Savegame)
	uint32 Id = 0;

protected:

	UPROPERTY(NotReplicated, SaveGame)
	TArray<FAttrModifier> BaseModifiers;

	UPROPERTY(NotReplicated, SaveGame)
	TArray<FAttributeCategoryMods> CategoryMods;


public:

	FBaseAttr() : Id(IdCount++) {}
	virtual ~FBaseAttr() {}

	void AddModifier(const FAttrModifier& Modifier, const FAttrCategory& Category = FAttrCategory::NoCategory);
	bool RemoveModifier(const FAttrModifier& Modifier, const FAttrCategory& Category = FAttrCategory::NoCategory, bool bRemoveFromAllCategories = false);

	/**
	* Get all modifiers of a category, base mods will be returned if category is None
	* @return Modifiers of a category as an Array
	*/
	const TArray<FAttrModifier>& GetModifiers(const FAttrCategory Category = FAttrCategory::NoCategory) const;

	/**
	* Get all categories where the attribute has any modifiers
	* @return Categories of an attribute as an Array
	*/
	void GetModifiedCategories(TArray<FAttrCategory>& OutCategories) const;
	void CleanCategoryModifiers(const FAttrCategory& Category);
	void CleanModifiers();

	void RefreshValue() { InternalRefreshValue({}); }

	// Compare two attributes by Id
	FORCEINLINE bool operator==(const FBaseAttr& Other) const { return Id == Other.Id; }

protected:

	virtual void InternalRefreshValue(FAttributeChangeInfo&& ChangeInfo) {}
};
