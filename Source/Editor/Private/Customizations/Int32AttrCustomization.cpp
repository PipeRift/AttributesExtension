// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "Customizations/Int32AttrCustomization.h"

#include <DetailWidgetRow.h>
#include <IDetailChildrenBuilder.h>
#include <Editor/UnrealEdEngine.h>

#include "Int32Attr.h"

#define LOCTEXT_NAMESPACE "FInt32AttrCustomization"


FInt32AttrCustomization::~FInt32AttrCustomization()
{
	GEditor->UnregisterForUndo(this);
	BaseValueChanged.Unbind();
}

void FInt32AttrCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	GEditor->RegisterForUndo(this);

	BaseValueHandle = StructPropertyHandle->GetChildHandle({ "BaseValue" });
	ValueHandle = StructPropertyHandle->GetChildHandle({ "Value" });

	BaseValueChanged.BindRaw(this, &FInt32AttrCustomization::RefreshValue);
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

void FInt32AttrCustomization::RefreshValue()
{
	if (!BaseValueHandle.IsValid() || !ValueHandle.IsValid())
	{
		return;
	}

	int32 BaseValue;
	if (BaseValueHandle->GetValue(BaseValue) == FPropertyAccess::Success)
	{
		ValueHandle->SetValue(BaseValue, EPropertyValueSetFlags::NotTransactable);
	}
}

#undef LOCTEXT_NAMESPACE
