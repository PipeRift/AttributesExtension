// Copyright 2015-2018 Piperift. All Rights Reserved.

#include "FloatAttrCustomization.h"

#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"

#include "FloatAttr.h"

#define LOCTEXT_NAMESPACE "FFloatAttributeCustomization"


void FFloatAttrCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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

void FFloatAttrCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	/*TSharedPtr<IPropertyHandle> ModifiersHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FFloatAttr, BaseModifiers));
	StructBuilder.AddProperty(ModifiersHandle.ToSharedRef());*/
}

FText FFloatAttrCustomization::GetTextFromHandle(TSharedRef<IPropertyHandle> Handle) const
{
	FName Text;
	Handle->GetValue(Text);
	return FText::FromName(Text);
}


#undef LOCTEXT_NAMESPACE
