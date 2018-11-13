// Copyright 2015-2018 Piperift. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "AttrModifier.h"
#include "AttrCategory.h"

#include "FloatAttr.generated.h"


UENUM(BlueprintType)
enum class EAttributeOperation : uint8
{
	AO_None       UMETA(DisplayName = "None"),
	AO_Add        UMETA(DisplayName = "Add"),
	AO_Remove     UMETA(DisplayName = "Remove"),
	AO_RemoveAll  UMETA(DisplayName = "Remove All"),
	AO_RemoveCategory  UMETA(DisplayName = "Remove Category"),
	AO_Base       UMETA(DisplayName = "Base Changed")
};


DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAttributeModifiedDelegate, const EAttributeOperation, Operation, const FAttrModifier&, Modifier, const FAttrCategory&, Category);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeModifiedMCDelegate, const EAttributeOperation, Operation, const FAttrModifier&, Modifier, const FAttrCategory&, Category);


/**
 * Float Attribute
 * Used as a modular float depending on modifiers
 */
USTRUCT(BlueprintType, meta = (HiddenByDefault))
struct ATTRIBUTES_API FFloatAttr
{
	GENERATED_BODY()

	/** Using an static counter for Ids.
	 * Reduces Id from 16 to 4 bytes.
	 * If you need more, change ids to 64
	 */
	FFloatAttr(float BaseValue = 0.f)
		: BaseValue{ BaseValue }
		, Value { BaseValue }
		, Id(IdCount++)
	{}


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	float BaseValue;

private:

	UPROPERTY()
	uint32 Id;

	UPROPERTY()
	float Value;

	UPROPERTY(NotReplicated)
	TArray<FAttrModifier> BaseModifiers;

	UPROPERTY(NotReplicated)
	TArray<FAttributeCategoryMods> CategoryMods;

public:

	UPROPERTY()
	FAttributeModifiedMCDelegate OnModified;


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

	void SetBaseValue(float NewValue);
	float GetBaseValue() const { return BaseValue; }
	float GetValue() const { return Value; }

	void RefreshValue();


	/* Get Attribute final value */
	FORCEINLINE operator float() const { return GetValue(); }

	//compare two modifications by guid
	FORCEINLINE bool operator==(const FFloatAttr& Other) const { return Id == Other.Id; }

	FORCEINLINE float operator+(const float Other) const { return GetValue() + Other; }

	FORCEINLINE float operator-(const float Other) const { return GetValue() - Other; }

	FORCEINLINE float operator+(const FFloatAttr& Other) const { return *this + Other.GetValue(); }

	FORCEINLINE float operator-(const FFloatAttr& Other) const { return *this - Other.GetValue(); }

	void PostSerialize(const FArchive& Ar);

private:

	static uint32 IdCount;
};

template<>
struct TStructOpsTypeTraits<FFloatAttr> : public TStructOpsTypeTraitsBase2<FFloatAttr>
{
	enum
	{
		WithPostSerialize = true
	};
};
