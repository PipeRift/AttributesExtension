// Copyright 2015-2020 Piperift. All Rights Reserved.

#include "Customizations/FloatAttrCustomization.h"

#include <DetailWidgetRow.h>
#include <IDetailChildrenBuilder.h>
#include <Editor/UnrealEdEngine.h>

#include "FloatAttr.h"

#define LOCTEXT_NAMESPACE "FFloatAttrCustomization"


FFloatAttrCustomization::~FFloatAttrCustomization()
{
	GEditor->UnregisterForUndo(this);
	BaseValueChanged.Unbind();
}

void FFloatAttrCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	GEditor->RegisterForUndo(this);

	BaseValueHandle = StructPropertyHandle->GetChildHandle({ "BaseValue" });
	ValueHandle = StructPropertyHandle->GetChildHandle({ "Value" });

	BaseValueChanged.BindRaw(this, &FFloatAttrCustomization::RefreshValue);
	BaseValueHandle->SetOnPropertyValueChanged(BaseValueChanged);

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

void FFloatAttrCustomization::RefreshValue()
{
	if (!BaseValueHandle.IsValid() || !ValueHandle.IsValid())
	{
		return;
	}

	float BaseValue;
	if (BaseValueHandle->GetValue(BaseValue) == FPropertyAccess::Success)
	{
		ValueHandle->SetValue(BaseValue, EPropertyValueSetFlags::NotTransactable);
	}
}

#undef LOCTEXT_NAMESPACE
