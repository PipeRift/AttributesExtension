// Copyright 2015-2020 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "FloatAttr.h"

#include "FloatAttributesLibrary.generated.h"


/**
 *
 */
UCLASS()
class ATTRIBUTES_API UFloatAttributesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** @return true when two Attributes are the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "=="))
	static FORCEINLINE bool Is(const FFloatAttr& A, const FFloatAttr& B) { return A == B; }

	/** @return true when two Attributes are not the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "!="))
	static FORCEINLINE bool IsNot(const FFloatAttr& A, const FFloatAttr& B) { return A != B; }

	/** @return true if two attributes have the same base value */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static FORCEINLINE bool Equals(const FFloatAttr& A, const FFloatAttr& B)
	{
		return A.GetBaseValue() == B.GetBaseValue();
	}

	/**
	 * Get the final value of an attribute
	 * @param Attribute to get value from
	 * @return the final value
	 */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (Keywords = "get value float total final"))
	static FORCEINLINE float GetValue(const FFloatAttr& Attribute) { return Attribute.GetValue(); }

	// Get final value
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (DisplayName = "ToFloat (FloatAttr)", CompactNodeTitle = "->", Keywords = "get value float", BlueprintAutocast))
	static FORCEINLINE float Conv_AttributeToFloat(const FFloatAttr& Attribute) { return GetValue(Attribute); }

	// Get final value as double
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (DisplayName = "ToDouble (FloatAttr)", CompactNodeTitle = "->", Keywords = "get value double", BlueprintAutocast))
	static FORCEINLINE double Conv_AttributeToDouble(const FFloatAttr& Attribute) { return GetValue(Attribute); }

	// Get final value as String
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (DisplayName = "ToString (FloatAttr)", CompactNodeTitle = "->", BlueprintAutocast))
	static FORCEINLINE FString Conv_AttributeToString(const FFloatAttr& Attribute) {
		return FString::SanitizeFloat(GetValue(Attribute));
	}

	/**
	 * Get the base value of an attribute
	 * @param Attribute to get base value from
	 * @return the base value
	 */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static FORCEINLINE float GetBase(const FFloatAttr& Attribute) { return Attribute.GetBaseValue(); }

	/**
	 * Set the base value of an attribute
	 * @param Attribute to set base value at
	 * @param Value to set as the base value
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void SetBase(UPARAM(ref) FFloatAttr& Attribute, float Value) { Attribute.SetBaseValue(Value); }

	/**
	 * Adds a modifier to an attribute
	 * @param Attribute to be modified
	 * @param Modifier to apply to the attribute
	 * @param Category of the modifier (Optional)
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void AddModifier(UPARAM(ref) FFloatAttr& Attribute, const FAttrModifier& Modifier, const FAttrCategory Category)
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
	UFUNCTION(BlueprintCallable, Category = Attributes, meta=(AdvancedDisplay="Category,bRemoveFromAllCategories"))
	static FORCEINLINE bool RemoveModifier(UPARAM(ref) FFloatAttr& Attribute, const FAttrModifier& Modifier, const FAttrCategory Category, bool bRemoveFromAllCategories = false)
	{
		return Attribute.RemoveModifier(Modifier, Category, bRemoveFromAllCategories);
	}

	/**
	 * Get all modifiers of a category, base mods will be returned if category is None
	 * @param Attribute to get modifiers from
	 * @return Modifiers of a category as an Array
	 */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void GetModifiers(const FFloatAttr& Attribute, const FAttrCategory Category, TArray<FAttrModifier>& Modifiers)
	{
		Modifiers = Attribute.GetModifiers(Category);
	}

	/**
	 * Get all categories where the attribute has any modifiers
	 * @param Attribute to get categories from
	 * @return Categories of an attribute as an Array
	 */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static void GetModifiedCategories(const FFloatAttr& Attribute, TArray<FAttrCategory>& Categories)
	{
		Attribute.GetModifiedCategories(Categories);
	}

	/**
	 * Remove all modifiers of an attribute
	 * @param Attribute to clean
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void CleanModifiers(UPARAM(ref) FFloatAttr& Attribute)
	{
		return Attribute.CleanModifiers();
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void CleanCategoryModifiers(UPARAM(ref) FFloatAttr& Attribute, const FAttrCategory Category)
	{
		Attribute.CleanCategoryModifiers(Category);
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void BindOnModified(UPARAM(ref) FFloatAttr& Attribute, const FFloatModifiedDelegate& Event)
	{
		Attribute.GetOnModified().AddUnique(Event);
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void UnbindOnModified(UPARAM(ref) FFloatAttr& Attribute, const FFloatModifiedDelegate& Event)
	{
		Attribute.GetOnModified().Remove(Event);
	}

protected:

	UFUNCTION(BlueprintPure, Category = Attributes)
	static void Make(float BaseValue, FFloatAttr& FloatAttr) { FloatAttr = { BaseValue }; }

	UFUNCTION(BlueprintPure, Category = Attributes)
	static void Break(const FFloatAttr& FloatAttr, float& BaseValue, float& Value) {
		BaseValue = FloatAttr.GetBaseValue();
		Value = FloatAttr.GetValue();
	}
};
