// Copyright 2015-2023 Piperift. All Rights Reserved.

#include "Customizations/AttrCategoryCustomization.h"

#include "AttrCategory.h"
#include "AttributesModule.h"
#include "AttributesSettings.h"


#define LOCTEXT_NAMESPACE "FAttrCategoryCustomization"


bool FAttrCategoryCustomization::CanCustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle,
	class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructHandle = StructPropertyHandle;
	NameHandle = StructPropertyHandle->GetChildHandle("Name");

	if (NameHandle->IsValidHandle())
	{
		FAttributesModule& Module = FAttributesModule::Get();
		// Bind On Settings Changed event
		Module.OnModifiedSettings().BindRaw(this, &FAttrCategoryCustomization::UpdateItems);
		return true;
	}
	return false;
}

void FAttrCategoryCustomization::GetAllItems(TArray<FString>& Values) const
{
	const UAttributesSettings* Settings = GetDefault<UAttributesSettings>();
	if (!Settings)
		return;

	for (const auto& Category : Settings->GetCategories())
	{
		Values.Add(Category.ToString());
	}
	// Make sure None is at the start
	Values.Remove(FName{}.ToString());
	Values.Insert(FName{}.ToString(), 0);
}

void FAttrCategoryCustomization::OnItemSelected(FString Value)
{
	const TSet<FName>& AllCategories = GetDefault<UAttributesSettings>()->GetCategories();

	FName NameValue = FName(*Value);

	if (!NameValue.IsNone() && AllCategories.Contains(NameValue))
	{
		NameHandle->SetValue(NameValue);
	}
	else
	{
		// Priority not found. Set default value
		NameHandle->SetValue(NAME_None);
	}
}

/** Display the current column selection */
FText FAttrCategoryCustomization::GetSelectedText() const
{
	FName Name;
	const FPropertyAccess::Result RowResult = NameHandle->GetValue(Name);
	const TSet<FName>& AllCategories = GetDefault<UAttributesSettings>()->GetCategories();

	if (RowResult != FPropertyAccess::MultipleValues)
	{
		if (AllCategories.Contains(Name))
		{
			return FText::FromName(Name);
		}
		return FText::FromName(NAME_None);
	}
	return LOCTEXT("MultipleValues", "Multiple Values");
}

#undef LOCTEXT_NAMESPACE
