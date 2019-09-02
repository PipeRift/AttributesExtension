// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "Customizations/Int32AttrCustomization.h"

#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"

#include "Int32Attr.h"

#define LOCTEXT_NAMESPACE "FInt32AttributeCustomization"


void FInt32AttrCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	TSharedPtr<IPropertyHandle> BaseValueHandle = StructPropertyHandle->GetChildHandle({"BaseValue"});

	HeaderRow.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(200.f)
	[
		BaseValueHandle->CreatePropertyValueWidget()
	];
}

void FInt32AttrCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	/*TSharedPtr<IPropertyHandle> ModifiersHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FFloatAttr, BaseModifiers));
	StructBuilder.AddProperty(ModifiersHandle.ToSharedRef());*/
}

FText FInt32AttrCustomization::GetTextFromHandle(TSharedRef<IPropertyHandle> Handle) const
{
	FName Text;
	Handle->GetValue(Text);
	return FText::FromName(Text);
}


#undef LOCTEXT_NAMESPACE
