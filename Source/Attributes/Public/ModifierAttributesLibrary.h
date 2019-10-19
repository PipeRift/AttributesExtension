// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "AttrModifier.h"

#include "ModifierAttributesLibrary.generated.h"


UCLASS()
class ATTRIBUTES_API UModifierAttributesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/** @return true when two Attributes are the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "=="))
	static FORCEINLINE bool Is(const FAttrModifier& A, const FAttrModifier& B) { return A == B; }

	/** @return true when two Attributes are not the same */
	UFUNCTION(BlueprintPure, Category = Attributes, meta = (CompactNodeTitle = "!="))
	static FORCEINLINE bool IsNot(const FAttrModifier& A, const FAttrModifier& B) { return A != B; }

	/** Stack other modifiers values into this mod.
	 * Now applying this modifier will be equivalent to applying all the others at the same time
	 * @param Mods to be stacked together as one
	 * @return the resulting stacked mod
	 */
	UFUNCTION(BlueprintPure, Category = "Attributes|Modifiers")
	static void StackMods(UPARAM(ref) FAttrModifier& TargetMod, const TArray<FAttrModifier>& Mods) {
		TargetMod.StackMods(Mods);
	}

	/** Stack other modifier's values into target mod.
	 * Applying this mod will be equivalent to applying both
	 * @param TargetMod to be modified
	 * @param OtherMod to be stacked into TargetMod
	 */
	UFUNCTION(BlueprintCallable, Category = "Attributes|Modifiers")
	static void StackMod(UPARAM(ref) FAttrModifier& TargetMod, const FAttrModifier& OtherMod) {
		TargetMod.StackMod(OtherMod);
	}

	UFUNCTION(BlueprintCallable, Category = "Attributes|Modifiers", meta = (Keywords = "copy"))
	static void SetValues(UPARAM(ref) FAttrModifier& Target, const FAttrModifier& Values) {
		Target.SetValues(Values);
	}
};
