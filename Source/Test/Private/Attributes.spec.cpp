// Copyright 2015-2026 Piperift. All Rights Reserved.

#include "Automatron.h"
#include "FloatAttr.h"
#include "Int32Attr.h"


class FAttributesSpec : public Automatron::FTestSpec
{
	GENERATE_SPEC(FAttributesSpec, "Attributes",
		EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask);
};

void FAttributesSpec::Define()
{
	Describe("Float", [this]() {
		It("Attributes can be instantiated empty", [this]() {
			FFloatAttr Attr;
			TestTrue(TEXT("Base Value is set"), Attr.GetBaseValue() == 0.0f);
			TestTrue(TEXT("Value is set"), Attr == 0.0f);
		});

		It("Attributes can be instantiated with a base value", [this]() {
			FFloatAttr Attr{5.f};
			TestTrue(TEXT("Base Value is set"), Attr.GetBaseValue() == 5.0f);
			TestTrue(TEXT("Base Value is set"), Attr == 5.0f);
		});
	});

	Describe("Int32", [this]() {
		It("Attributes can be instantiated empty", [this]() {
			FInt32Attr Attr;
			TestTrue(TEXT("Base Value"), Attr.GetBaseValue() == 0);
			TestTrue(TEXT("Value"), Attr == 0);
		});

		It("Attributes can be instantiated with a base value", [this]() {
			FInt32Attr Attr{5};
			TestTrue(TEXT("Base Value"), Attr.GetBaseValue() == 5);
			TestTrue(TEXT("Value"), Attr == 5);
		});
	});

	Describe("Modifiers", [this]() {
	});
}
