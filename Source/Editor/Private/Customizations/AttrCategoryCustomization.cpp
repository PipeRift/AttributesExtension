// Copyright 2015-2020 Piperift. All Rights Reserved.

#include "Customizations/AttrCategoryCustomization.h"

#include "AttributesModule.h"

#include "AttrCategory.h"
#include "AttributesSettings.h"

#define LOCTEXT_NAMESPACE "FAttrCategoryCustomization"


bool FAttrCategoryCustomization::CanCustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructHandle = StructPropertyHandle;
	NameHandle = StructPropertyHandle->GetChildHandle("Name");

	if (NameHandle->IsValidHandle())
	{
		FAttributesModule& Module = FAttributesModule::Get();
		//Bind On Settings Changed event
		Module.OnModifiedSettings().BindRaw(this, &FAttrCategoryCustomization::UpdateItems);
		return true;
	}
	return false;
}

void FAttrCategoryCustomization::GetAllItems(TArray<FString>& Values) const {
	const UAttributesSettings* Settings = GetDefault<UAttributesSettings>();
	if (!Settings)
		return;

	for (const auto& Category : Settings->GetCategories())
	{
		Values.Add(Category.ToString());
	}
	// Make sure None is at the start
	Values.Remove(NO_ATTRCATEGORY_NAME.ToString());
	Values.Insert(NO_ATTRCATEGORY_NAME.ToString(), 0);
}

void FAttrCategoryCustomization::OnItemSelected(FString Value)
{
	const TSet<FName>& AllCategories = GetDefault<UAttributesSettings>()->GetCategories();

	FName NameValue = FName(*Value);

	if (NameValue != NO_ATTRCATEGORY_NAME && AllCategories.Contains(NameValue))
	{
		NameHandle->SetValue(NameValue);
	}
	else
	{
		//Priority not found. Set default value
		NameHandle->SetValue(NO_ATTRCATEGORY_NAME);
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
		return FText::FromName(NO_ATTRCATEGORY_NAME);
	}
	return LOCTEXT("MultipleValues", "Multiple Values");
}

#undef LOCTEXT_NAMESPACE
