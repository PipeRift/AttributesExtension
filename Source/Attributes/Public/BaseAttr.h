// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "AttrModifier.h"
#include "AttrCategory.h"

#include "BaseAttr.generated.h"


UENUM(BlueprintType)
enum class EAttributeOperation : uint8
{
	None,
	Add,
	Remove,
	RemoveAll,
	RemoveCategory,
	Base
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAttributeModifiedDelegate, const EAttributeOperation, Operation, const FAttrModifier&, Modifier, const FAttrCategory&, Category);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeModifiedMCDelegate, const EAttributeOperation, Operation, const FAttrModifier&, Modifier, const FAttrCategory&, Category);


/**
 * Base Attribute
 * Extended upon to support different types of attributes
 */
USTRUCT()
struct FBaseAttr
{
	GENERATED_BODY()


private:

	/** Using an static counter for Ids.
	 * Reduces Id from 16 to 4 bytes.
	 * If you need more, change ids to 64
	 */
	static uint32 IdCount;

	UPROPERTY(Savegame)
	uint32 Id;

protected:

	UPROPERTY(NotReplicated, SaveGame)
	TArray<FAttrModifier> BaseModifiers;

	UPROPERTY(NotReplicated, SaveGame)
	TArray<FAttributeCategoryMods> CategoryMods;

public:

	UPROPERTY()
	FAttributeModifiedMCDelegate OnModified;


	FBaseAttr() : Id(IdCount++) {}
	virtual ~FBaseAttr() {}

public:

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

	virtual void RefreshValue() {}

	// Compare two attributes by Id
	FORCEINLINE bool operator==(const FBaseAttr& Other) const { return Id == Other.Id; }
};
