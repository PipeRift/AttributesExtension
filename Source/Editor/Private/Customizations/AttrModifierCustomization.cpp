// Copyright 2015-2023 Piperift. All Rights Reserved.

#include "Customizations/AttrModifierCustomization.h"

#include "AttrModifier.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"


#define LOCTEXT_NAMESPACE "FAttrModifierCustomization"


void FAttrModifierCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle,
	class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructHandle = StructPropertyHandle;
	IncrementHandle = StructHandle->GetChildHandle({GET_MEMBER_NAME_CHECKED(FAttrModifier, Increment)});
	LastMultiplierHandle =
		StructHandle->GetChildHandle({GET_MEMBER_NAME_CHECKED(FAttrModifier, LastMultiplier)});
	BaseMultiplierHandle =
		StructHandle->GetChildHandle({GET_MEMBER_NAME_CHECKED(FAttrModifier, BaseMultiplier)});

	HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()].ValueContent().MinDesiredWidth(
		200.f)
		[SNew(STextBlock).Text(this, &FAttrModifierCustomization::GetValueHelpText).Margin(FMargin{2, 0})];
}

void FAttrModifierCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	const bool bHideIncrement = StructHandle->HasMetaData("HideIncrement");
	const bool bHideLastMultiplier = StructHandle->HasMetaData("HideLastMultiplier");
	const bool bHideBaseMultiplier = StructHandle->HasMetaData("HideBaseMultiplier");

	TSharedRef<SHorizontalBox> ModListWidget = SNew(SHorizontalBox);

	if (!bHideIncrement)
	{
		ModListWidget->AddSlot()
			.HAlign(HAlign_Fill)
			.MaxWidth(100.f)
			.Padding(
				2, 0)[SNew(SVerticalBox) + SVerticalBox::Slot()[IncrementHandle->CreatePropertyNameWidget()] +
					  SVerticalBox::Slot().HAlign(HAlign_Fill)[IncrementHandle->CreatePropertyValueWidget()]];
	}

	if (!bHideLastMultiplier)
	{
		ModListWidget->AddSlot()
			.HAlign(HAlign_Fill)
			.MaxWidth(100.f)
			.Padding(2, 0)[SNew(SVerticalBox) +
						   SVerticalBox::Slot()[LastMultiplierHandle->CreatePropertyNameWidget()] +
						   SVerticalBox::Slot().HAlign(
							   HAlign_Fill)[LastMultiplierHandle->CreatePropertyValueWidget()]];
	}

	if (!bHideBaseMultiplier)
	{
		ModListWidget->AddSlot()
			.HAlign(HAlign_Fill)
			.MaxWidth(100.f)
			.Padding(2, 0)[SNew(SVerticalBox) +
						   SVerticalBox::Slot()[BaseMultiplierHandle->CreatePropertyNameWidget()] +
						   SVerticalBox::Slot().HAlign(
							   HAlign_Fill)[BaseMultiplierHandle->CreatePropertyValueWidget()]];
	}

	StructBuilder.AddCustomRow(LOCTEXT("Search", "Values"))
		.ValueContent()
		.MinDesiredWidth(500.f)[ModListWidget];
}

FText FAttrModifierCustomization::GetValueHelpText() const
{
	FString Text{};

	float Increment;
	if (IncrementHandle->GetValue(Increment) == FPropertyAccess::Success && Increment != 0)
	{
		if (Increment > 0)
		{
			Text.Appendf(TEXT("+%g  "), Increment);
		}
		else
		{
			Text.Appendf(TEXT("%g  "), Increment);
		}
	}

	float LastMultiplier;
	if (LastMultiplierHandle->GetValue(LastMultiplier) == FPropertyAccess::Success &&
		!FMath::IsNearlyZero(LastMultiplier))
	{
		if (LastMultiplier > 0.f)
		{
			Text.Appendf(TEXT("+%g%%  "), LastMultiplier * 100.f);
		}
		else
		{
			Text.Appendf(TEXT("%g%%  "), LastMultiplier * 100.f);
		}
	}

	float BaseMultiplier;
	if (BaseMultiplierHandle->GetValue(BaseMultiplier) == FPropertyAccess::Success &&
		!FMath::IsNearlyZero(BaseMultiplier))
	{
		if (BaseMultiplier > 0.f)
		{
			Text.Appendf(TEXT("+%g%% base  "), BaseMultiplier * 100.f);
		}
		else
		{
			Text.Appendf(TEXT("%g%% base  "), BaseMultiplier * 100.f);
		}
	}

	return FText::FromString(Text);
}

#undef LOCTEXT_NAMESPACE
