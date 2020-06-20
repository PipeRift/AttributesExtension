// Copyright 2015-2020 Piperift. All Rights Reserved.

#include "Customizations/AttrCategoryPin.h"

#include "Kismet2/KismetEditorUtilities.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"

#include "AttrCategory.h"
#include "AttributesModule.h"
#include "AttributesSettings.h"


void SAttrCategoryPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	FAttributesModule& Module = FAttributesModule::Get();

	//Bind On Settings Changed event
	Module.OnModifiedSettings().BindRaw(this, &SAttrCategoryPin::UpdateItems, false);

	SStringEnumPin::Construct(SStringEnumPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SAttrCategoryPin::GetDefaultValueWidget()
{
	//Get actual default value
	ParseDefaultValue();

	return SStringEnumPin::GetDefaultValueWidget();
}

void SAttrCategoryPin::ParseDefaultValue()
{
	FString NameString = GraphPinObj->GetDefaultAsString();
	if (NameString.StartsWith(TEXT("(")) && NameString.EndsWith(TEXT(")")))
	{
		//Remove ( and )
		NameString = NameString.LeftChop(1);
		NameString = NameString.RightChop(1);

		//Get parameter string value
		NameString.Split("=", nullptr, &NameString);
		if (NameString.StartsWith(TEXT("\"")) && NameString.EndsWith(TEXT("\"")))
		{
			NameString = NameString.LeftChop(1);
			NameString = NameString.RightChop(1);
		}
	}
	else
	{
		// NameString is invalid
		NameString = {};
	}

	if (!NameString.IsEmpty())
	{
		DefaultNameValue = FName(*NameString);
	}
	else
	{
		DefaultNameValue = NO_ATTRCATEGORY_NAME;
	}
}

void SAttrCategoryPin::ApplyDefaultValue()
{
	// Set Pin Data
	FString PriorityString;
	if (!DefaultNameValue.IsNone())
	{
		PriorityString = TEXT("(");
		PriorityString += TEXT("Name=\"");
		PriorityString += DefaultNameValue.ToString();
		PriorityString += TEXT("\")");
	}
	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();
	if (CurrentDefaultValue.IsEmpty())
	{
		CurrentDefaultValue = FString(TEXT("()"));
	}
	if (!CurrentDefaultValue.Equals(PriorityString))
	{
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, PriorityString);
	}
}


void SAttrCategoryPin::GetEnumItems(TArray<FString>& Values)
{
	const UAttributesSettings* Settings = GetDefault<UAttributesSettings>();
	if (!Settings) {
		return;
	}

	for (const auto& Category : Settings->GetCategories())
	{
		Values.Add(Category.ToString());
	}
	// Make sure None is at the start
	Values.Remove(NO_ATTRCATEGORY_NAME.ToString());
	Values.Insert(NO_ATTRCATEGORY_NAME.ToString(), 0);
}

void SAttrCategoryPin::OnItemSelected(FString Value)
{
	const TSet<FName>& AllCategories = GetDefault<UAttributesSettings>()->GetCategories();

	FName NameValue = FName(*Value);

	//If Category not found, Set default value
	if (NameValue != NO_ATTRCATEGORY_NAME && AllCategories.Contains(NameValue))
		DefaultNameValue = NameValue;
	else
		DefaultNameValue = NO_ATTRCATEGORY_NAME;

	ApplyDefaultValue();
}

FText SAttrCategoryPin::GetSelectedItem() const
{
	//Call parent but don't use it. This is for widget logic
	SStringEnumPin::GetSelectedItem();

	const TSet<FName>& AllCategories = GetDefault<UAttributesSettings>()->GetCategories();

	if (AllCategories.Contains(DefaultNameValue))
	{
		//Return name with prefix number
		return FText::FromName(DefaultNameValue);
	}
	return FText::FromName(NO_ATTRCATEGORY_NAME);
}
