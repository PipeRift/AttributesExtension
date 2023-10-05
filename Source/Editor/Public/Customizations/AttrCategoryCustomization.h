// Copyright 2015-2023 Piperift. All Rights Reserved.

#pragma once

#include "Customizations/StringEnumCustomization.h"
#include "PropertyHandle.h"



class FAttrCategoryCustomization : public FStringEnumCustomization
{
public:
	/**
	 * Creates a new instance.
	 *
	 * @return A new struct customization for Factions.
	 */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FAttrCategoryCustomization);
	}

protected:
	/** Handle to the struct properties being customized */
	TSharedPtr<IPropertyHandle> StructHandle;
	TSharedPtr<IPropertyHandle> NameHandle;

	virtual bool CanCustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle,
		class FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	/** Returns all the enum items.
	 * This is for override purposes.
	 */
	virtual void GetAllItems(TArray<FString>& Values) const override;

	/** Returns all the enum items.
	 * This is for override purposes.
	 */
	virtual void OnItemSelected(FString Value) override;

	virtual FText GetSelectedText() const override;
};
