// Copyright 2015-2023 Piperift. All Rights Reserved.

#pragma once

#include "Int32Attr.h"

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "Int32AttributesLibrary.generated.h"


/**
 *
 */
UCLASS()
class ATTRIBUTES_API UInt32AttributesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** @return true when two Attributes are the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "=="))
	static FORCEINLINE bool Is(const FInt32Attr& A, const FInt32Attr& B)
	{
		return A == B;
	}

	/** @return true when two Attributes are not the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "!="))
	static FORCEINLINE bool IsNot(const FInt32Attr& A, const FInt32Attr& B)
	{
		return A != B;
	}

	/** @return true if two attributes have the same base value */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static FORCEINLINE bool Equals(const FInt32Attr& A, const FInt32Attr& B)
	{
		return A.GetBaseValue() == B.GetBaseValue();
	}

	/**
	 * Get the final value of an attribute
	 * @param Attribute to get value from
	 * @return the final value
	 */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (Keywords = "get value int total final"))
	static FORCEINLINE int32 GetValue(const FInt32Attr& Attribute)
	{
		return Attribute.GetValue();
	}

	// Get final value
	UFUNCTION(BlueprintPure, Category = Attributes,
		meta = (DisplayName = "ToInt (Int32Attr)", CompactNodeTitle = "->", Keywords = "get value int",
			BlueprintAutocast))
	static FORCEINLINE int32 Conv_AttributeToInt(const FInt32Attr& Attribute)
	{
		return GetValue(Attribute);
	}

	// Get final value as String
	UFUNCTION(BlueprintPure, Category = Attributes,
		meta = (DisplayName = "ToString (Int32Attr)", CompactNodeTitle = "->", BlueprintAutocast))
	static FORCEINLINE FString Conv_AttributeToString(const FInt32Attr& Attribute)
	{
		return FString::SanitizeFloat(GetValue(Attribute));
	}

	/**
	 * Get the base value of an attribute
	 * @param Attribute to get base value from
	 * @return the base value
	 */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static FORCEINLINE int GetBase(const FInt32Attr& Attribute)
	{
		return Attribute.GetBaseValue();
	}

	/**
	 * Set the base value of an attribute
	 * @param Attribute to set base value at
	 * @param Value to set as the base value
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void SetBase(UPARAM(ref) FInt32Attr& Attribute, int32 Value)
	{
		Attribute.SetBaseValue(Value);
	}

	/**
	 * Adds a modifier to an attribute
	 * @param Attribute to be modified
	 * @param Modifier to apply to the attribute
	 * @param Category of the modifier (Optional)
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void AddModifier(
		UPARAM(ref) FInt32Attr& Attribute, const FAttrModifier& Modifier, const FAttrCategory Category)
	{
		Attribute.AddModifier(Modifier, Category);
	}

	/**
	 * Removes a modifier from an attribute
	 * @param Attribute to be modified
	 * @param Modifier to remove from the attribute
	 * @param Category of the modifier (Optional)
	 * @return true if any modifier was removed
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes,
		meta = (AdvancedDisplay = "Category,bRemoveFromAllCategories"))
	static FORCEINLINE bool RemoveModifier(UPARAM(ref) FInt32Attr& Attribute, const FAttrModifier& Modifier,
		const FAttrCategory Category, bool bRemoveFromAllCategories = false)
	{
		return Attribute.RemoveModifier(Modifier, Category, bRemoveFromAllCategories);
	}

	/**
	 * Get all modifiers of a category, base mods will be returned if category is None
	 * @param Attribute to get modifiers from
	 * @return Modifiers of a category as an Array
	 */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void GetModifiers(
		const FInt32Attr& Attribute, const FAttrCategory Category, TArray<FAttrModifier>& Modifiers)
	{
		Modifiers = Attribute.GetModifiers(Category);
	}

	/**
	 * Get all categories where the attribute has any modifiers
	 * @param Attribute to get categories from
	 * @return Categories of an attribute as an Array
	 */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static void GetModifiedCategories(const FInt32Attr& Attribute, TArray<FAttrCategory>& Categories)
	{
		Attribute.GetModifiedCategories(Categories);
	}

	/**
	 * Remove all modifiers of an attribute
	 * @param Attribute to clean
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void CleanModifiers(UPARAM(ref) FInt32Attr& Attribute)
	{
		return Attribute.CleanModifiers();
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void CleanCategoryModifiers(UPARAM(ref) FInt32Attr& Attribute, const FAttrCategory Category)
	{
		Attribute.CleanCategoryModifiers(Category);
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void BindOnModified(UPARAM(ref) FInt32Attr& Attribute, const FInt32ModifiedDelegate& Event)
	{
		Attribute.GetOnModified().AddUnique(Event);
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void UnbindOnModified(UPARAM(ref) FInt32Attr& Attribute, const FInt32ModifiedDelegate& Event)
	{
		Attribute.GetOnModified().Remove(Event);
	}

protected:
	UFUNCTION(BlueprintPure, Category = Attributes)
	static void Make(int32 BaseValue, FInt32Attr& IntAttr)
	{
		IntAttr = {BaseValue};
	}

	UFUNCTION(BlueprintPure, Category = Attributes)
	static void Break(const FInt32Attr& IntAttr, int32& BaseValue, int32& Value)
	{
		BaseValue = IntAttr.GetBaseValue();
		Value = IntAttr.GetValue();
	}
};
