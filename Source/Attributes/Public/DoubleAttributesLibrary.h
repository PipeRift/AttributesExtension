// Copyright 2015-2023 Piperift. All Rights Reserved.

#pragma once

#include "DoubleAttr.h"

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "DoubleAttributesLibrary.generated.h"


/**
 *
 */
UCLASS()
class ATTRIBUTES_API UDoubleAttributesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** @return true when two Attributes are the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "=="))
	static FORCEINLINE bool Is(const FDoubleAttr& A, const FDoubleAttr& B)
	{
		return A == B;
	}

	/** @return true when two Attributes are not the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "!="))
	static FORCEINLINE bool IsNot(const FDoubleAttr& A, const FDoubleAttr& B)
	{
		return A != B;
	}

	/** @return true if two attributes have the same base value */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static FORCEINLINE bool Equals(const FDoubleAttr& A, const FDoubleAttr& B)
	{
		return A.GetBaseValue() == B.GetBaseValue();
	}

	/**
	 * Get the final value of an attribute
	 * @param Attribute to get value from
	 * @return the final value
	 */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (Keywords = "get value double total final"))
	static FORCEINLINE double GetValue(const FDoubleAttr& Attribute)
	{
		return Attribute.GetValue();
	}

	// Get final value
	UFUNCTION(BlueprintPure, Category = Attributes,
		meta = (DisplayName = "ToFloat (DoubleAttr)", CompactNodeTitle = "->", Keywords = "get value double",
			BlueprintAutocast))
	static FORCEINLINE double Conv_AttributeToFloat(const FDoubleAttr& Attribute)
	{
		return GetValue(Attribute);
	}

	// Get final value as String
	UFUNCTION(BlueprintPure, Category = Attributes,
		meta = (DisplayName = "ToString (DoubleAttr)", CompactNodeTitle = "->", BlueprintAutocast))
	static FORCEINLINE FString Conv_AttributeToString(const FDoubleAttr& Attribute)
	{
		return FString::SanitizeFloat(GetValue(Attribute));
	}

	/**
	 * Get the base value of an attribute
	 * @param Attribute to get base value from
	 * @return the base value
	 */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static FORCEINLINE double GetBase(const FDoubleAttr& Attribute)
	{
		return Attribute.GetBaseValue();
	}

	/**
	 * Set the base value of an attribute
	 * @param Attribute to set base value at
	 * @param Value to set as the base value
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void SetBase(UPARAM(ref) FDoubleAttr& Attribute, double Value)
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
		UPARAM(ref) FDoubleAttr& Attribute, const FAttrModifier& Modifier, const FAttrCategory Category)
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
	static FORCEINLINE bool RemoveModifier(UPARAM(ref) FDoubleAttr& Attribute, const FAttrModifier& Modifier,
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
		const FDoubleAttr& Attribute, const FAttrCategory Category, TArray<FAttrModifier>& Modifiers)
	{
		Modifiers = Attribute.GetModifiers(Category);
	}

	/**
	 * Get all categories where the attribute has any modifiers
	 * @param Attribute to get categories from
	 * @return Categories of an attribute as an Array
	 */
	UFUNCTION(BlueprintPure, Category = Attributes)
	static void GetModifiedCategories(const FDoubleAttr& Attribute, TArray<FAttrCategory>& Categories)
	{
		Attribute.GetModifiedCategories(Categories);
	}

	/**
	 * Remove all modifiers of an attribute
	 * @param Attribute to clean
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void CleanModifiers(UPARAM(ref) FDoubleAttr& Attribute)
	{
		return Attribute.CleanModifiers();
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void CleanCategoryModifiers(UPARAM(ref) FDoubleAttr& Attribute, const FAttrCategory Category)
	{
		Attribute.CleanCategoryModifiers(Category);
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void BindOnModified(UPARAM(ref) FDoubleAttr& Attribute, const FFloatModifiedDelegate& Event)
	{
		Attribute.GetOnModified().AddUnique(Event);
	}

	UFUNCTION(BlueprintCallable, Category = Attributes, meta = (AdvancedDisplay = "Category"))
	static void UnbindOnModified(UPARAM(ref) FDoubleAttr& Attribute, const FFloatModifiedDelegate& Event)
	{
		Attribute.GetOnModified().Remove(Event);
	}

protected:
	UFUNCTION(BlueprintPure, Category = Attributes)
	static void Make(double BaseValue, FDoubleAttr& DoubleAttr)
	{
		DoubleAttr = {BaseValue};
	}

	UFUNCTION(BlueprintPure, Category = Attributes)
	static void Break(const FDoubleAttr& DoubleAttr, double& BaseValue, double& Value)
	{
		BaseValue = DoubleAttr.GetBaseValue();
		Value = DoubleAttr.GetValue();
	}
};
