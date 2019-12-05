// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "Customizations/Int32AttrCustomization.h"

#include <DetailWidgetRow.h>
#include <IDetailChildrenBuilder.h>
#include <Editor/UnrealEdEngine.h>
#include <UObject/Metadata.h>

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

	CopyMetadata(StructPropertyHandle, BaseValueHandle);

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

void FInt32AttrCustomization::CopyMetadata(TSharedPtr<IPropertyHandle> Origin, TSharedPtr<IPropertyHandle> Target)
{
	const auto * Metadata = UMetaData::GetMapForObject(Origin->GetMetaDataProperty());
	if (Metadata)
	{
		for (const auto& Item : *Metadata)
		{
			Target->SetInstanceMetaData(Item.Key, Item.Value);
		}
	}
}

#undef LOCTEXT_NAMESPACE
