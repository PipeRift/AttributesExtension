// Copyright 2015-2023 Piperift. All Rights Reserved.

#include "FloatAttr.h"
#include "Int32Attr.h"
#include "TestHelpers.h"


namespace
{
	constexpr uint32 Flags_Product =
		EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter;
	constexpr uint32 Flags_Smoke =
		EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter;
}	 // namespace

#define BASE_SPEC FAESpec

TESTSPEC(FFloatAttributesSpec, "AttributesExtension.Float", Flags_Smoke)
void FFloatAttributesSpec::Define()
{
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
}

TESTSPEC(FInt32AttributesSpec, "AttributesExtension.Int32", Flags_Smoke)
void FInt32AttributesSpec::Define()
{
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
}

TESTSPEC(FModifiersSpec, "AttributesExtension.Modifiers", Flags_Product)
void FModifiersSpec::Define() {}
