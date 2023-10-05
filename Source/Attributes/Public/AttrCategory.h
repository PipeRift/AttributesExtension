// Copyright 2015-2023 Piperift. All Rights Reserved.

#pragma once

#include "AttrModifier.h"
#include "AttributesSettings.h"

#include <CoreMinimal.h>

#include "AttrCategory.generated.h"


/**
 * Represents an existing AttrCategory from the database
 */
USTRUCT(BlueprintType)
struct ATTRIBUTES_API FAttrCategory
{
	GENERATED_BODY()

	static const FAttrCategory NoCategory;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Category)
	FName Name;


public:
	FAttrCategory() {}
	FAttrCategory(FName Name) : Name(Name) {}

	bool IsNone() const;

	/**
	 * Operator overloading & Hashes
	 */
	bool operator==(const FAttrCategory& Other) const
	{
		return Name == Other.Name;
	}
	bool operator!=(const FAttrCategory& Other) const
	{
		return !(*this == Other);
	}
	friend uint32 GetTypeHash(const FAttrCategory& InRelation)
	{
		return GetTypeHash(InRelation.Name);
	}

	FName GetName() const
	{
		return Name;
	}
};


USTRUCT()
struct FAttributeCategoryMods
{
	GENERATED_BODY()


	UPROPERTY()
	FAttrCategory Category;

	UPROPERTY()
	TArray<FAttrModifier> Modifiers;


	FAttributeCategoryMods() : Category(FAttrCategory::NoCategory) {}
	FAttributeCategoryMods(const FAttrCategory& Category) : Category(Category) {}

	friend bool operator<(const FAttributeCategoryMods& Self, const FAttributeCategoryMods& Other)
	{
		const TSet<FName>& Categories = GetDefault<UAttributesSettings>()->GetCategories();

		const FSetElementId SelfId = Categories.FindId(Self.Category.Name);
		const FSetElementId OtherId = Categories.FindId(Other.Category.Name);

		// Order by index. INDEX_NONE will be have priority (-1)
		return SelfId.AsInteger() < OtherId.AsInteger();
	}

	/**
	 * Operator overloading & Hashes
	 */
	FORCEINLINE bool operator==(const FAttrCategory& Other) const
	{
		return Category == Other;
	}
	FORCEINLINE bool operator!=(const FAttrCategory& Other) const
	{
		return !(*this == Other);
	}
};
