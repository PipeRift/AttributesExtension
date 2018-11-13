// Copyright 2015-2018 Piperift. All Rights Reserved.

#include "Customizations/StringEnumCustomization.h"
#include <PropertyHandle.h>
#include <DetailWidgetRow.h>

#define LOCTEXT_NAMESPACE "FStringEnumCustomization"

void FStringEnumCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	if (CanCustomizeHeader(StructPropertyHandle, HeaderRow, StructCustomizationUtils))
	{
		UpdateItems();

		HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MaxDesiredWidth(0.0f)
		.MinDesiredWidth(125.0f)
		[
			SAssignNew(ComboBox, SComboBox<TSharedPtr<FString>>)
			.OptionsSource(&CachedItems)
			.OnGenerateWidget(this, &FStringEnumCustomization::HandleStringEnumComboBoxGenerateWidget)
			.OnSelectionChanged(this, &FStringEnumCustomization::OnSelectionChanged)
			//.InitiallySelectedItem(GetVariableFactionValue())
			[
				SNew(STextBlock)
				.Text(this, &FStringEnumCustomization::GetSelectedText)
			]
		];
	}
}

void FStringEnumCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{}

/** Return the representation of the the column names to display */
TSharedRef<SWidget> FStringEnumCustomization::HandleStringEnumComboBoxGenerateWidget(TSharedPtr<FString> Item)
{
	return SNew(STextBlock)
		.Text(FText::FromString(*Item));
}

/** Update the root data on a change of selection */
void FStringEnumCustomization::OnSelectionChanged(TSharedPtr<FString> SelectedItem, ESelectInfo::Type SelectInfo)
{
	if (SelectedItem.IsValid()) {
		FString NewValue = **SelectedItem;

		UpdateItems();

		OnItemSelected(NewValue);
	}
}

/** Display the current column selection */
void FStringEnumCustomization::UpdateItems()
{
	Items.Empty();
	GetAllItems(Items);

	CachedItems.Empty();

	//Convert FString to Shared Ptrs and Populate the array
	for (auto It = Items.CreateConstIterator(); It; ++It)
	{
		if (!(*It).IsEmpty())
		{
			TSharedPtr<FString> Name = MakeShareable(new FString(*It));
			CachedItems.Add(Name);
		}
	}

	if (ComboBox.IsValid()) {
		ComboBox->RefreshOptions();
	}
}

void FStringEnumCustomization::GetAllItems(TArray<FString>& Values) const {
	Values.Add(FString("None"));
}

/** Display the current column selection */
FText FStringEnumCustomization::GetSelectedText() const
{
	return FText::FromString("None");
}


#undef LOCTEXT_NAMESPACE