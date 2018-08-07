// Copyright 2015-2018 Piperift. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameFramework/Actor.h"
#include "FloatAttr.h"

#include "AttributesFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class ATTRIBUTES_API UAttributesFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// Compare two Attributes by Id
	UFUNCTION(BlueprintPure, Category = "Attributes")
	static FORCEINLINE bool Is(UPARAM(ref) FFloatAttr& A, UPARAM(ref) FFloatAttr& B) { return A == B; }

	// Compare two Attributes by Base Value
	UFUNCTION(BlueprintPure, Category = "Attributes")
	static FORCEINLINE bool Equals(UPARAM(ref) FFloatAttr& A, UPARAM(ref) FFloatAttr& B)
	{
		return A.GetBaseValue() == B.GetBaseValue();
	}

	/**
	* Get the final value of an attribute
	* @param Attribute to get value from
	* @return the final value
	*/
	UFUNCTION(BlueprintPure, Category = "Attributes", meta = (Keywords = "get value float total final"))
	static FORCEINLINE float GetValue(const FFloatAttr& Attribute) { return Attribute.GetValue(); }

	// Get final value
	UFUNCTION(BlueprintPure, Category = "Attributes", meta = (DisplayName = "To Float", CompactNodeTitle = "->", Keywords = "get value float", BlueprintAutocast))
	static FORCEINLINE float Conv_AttributeToFloat(const FFloatAttr& Attribute) { return GetValue(Attribute); }

	/**
	 * Get the base value of an attribute
	 * @param Attribute to get base value from
	 * @return the base value
	 */
	UFUNCTION(BlueprintPure, Category = "Attributes")
	static FORCEINLINE float GetBase(const FFloatAttr& Attribute) { return Attribute.GetBaseValue(); }

	/**
	 * Set the base value of an attribute
	 * @param Attribute to set base value at
	 * @param Value to set as the base value
	 */
	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void SetBase(UPARAM(ref) FFloatAttr & Attribute, float Value) { Attribute.SetBaseValue(Value); }

	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "Category"))
	static void AddModifier(UPARAM(ref) FFloatAttr& Attribute, const FAttrModifier& Modifier, const FAttrCategory Category)
	{
		Attribute.AddModifier(Modifier, Category);
	}

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay="Category"))
	static void RemoveModifier(UPARAM(ref) FFloatAttr& Attribute, const FAttrModifier& Modifier, const FAttrCategory Category)
	{
		Attribute.RemoveModifier(Modifier, Category);
	}

	UFUNCTION(BlueprintPure, Category = Attributes)
	static FORCEINLINE TArray<FAttrModifier> GetModifiers(UPARAM(ref) FFloatAttr& Attribute)
	{
		return Attribute.GetModifiers();
	}

	UFUNCTION(BlueprintCallable, Category = Attributes)
	static void CleanModifiers(UPARAM(ref) FFloatAttr& Attribute)
	{
		return Attribute.CleanModifiers();
	}
};
