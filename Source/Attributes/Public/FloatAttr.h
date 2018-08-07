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
	AO_Remove     UMETA(DisplayName = "Remove")
};


DECLARE_DYNAMIC_DELEGATE_TwoParams(FModifiedDelegate, const EAttributeOperation, Operation, const FAttrModifier&, Modifier);


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
	FModifiedDelegate OnModified;


	void AddModifier(const FAttrModifier& Modifier, const FAttrCategory& Category = FAttrCategory::NoCategory);
	void RemoveModifier(const FAttrModifier& Modifier, const FAttrCategory& Category = FAttrCategory::NoCategory);

	const TArray<FAttrModifier>& GetModifiers(const FAttrCategory& Category = FAttrCategory::NoCategory);
	void CleanModifiers();

	void RefreshValue();


	void SetBaseValue(float NewValue) { BaseValue = NewValue; RefreshValue(); }
	float GetBaseValue() const { return BaseValue; }
	float GetValue() const { return Value; }

	/* Get Attribute final value */
	FORCEINLINE operator float() const { return GetValue(); }

	//compare two modifications by guid
	FORCEINLINE bool operator==(const FFloatAttr& Other) const { return Id == Other.Id; }

	FORCEINLINE float operator+(const float Other) const { return GetValue() + Other; }

	FORCEINLINE float operator-(const float Other) const { return GetValue() - Other; }

	FORCEINLINE float operator+(const FFloatAttr& Other) const { return *this + Other.GetValue(); }

	FORCEINLINE float operator-(const FFloatAttr& Other) const { return *this - Other.GetValue(); }


	void PostScriptConstruct() {
		RefreshValue();
	}

	/** Handles fix-up after importing from text */
	bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);


private:

	static uint32 IdCount;
};

template<>
struct TStructOpsTypeTraits<FFloatAttr> : public TStructOpsTypeTraitsBase2<FFloatAttr>
{
	enum
	{
		WithImportTextItem = true,
		WithPostScriptConstruct = true,
	};
};
