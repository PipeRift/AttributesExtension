// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Views/SListView.h"

class FAttrModifierCustomization : public IPropertyTypeCustomization
{
public:
	/**
	* Creates a new instance.
	*
	* @return A new struct customization for Anchor Type.
	*/
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FAttrModifierCustomization);
	}

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	FText GetValueHelpText() const;


	TSharedPtr<IPropertyHandle> StructHandle;
	TSharedPtr<IPropertyHandle> IncrementHandle;
	TSharedPtr<IPropertyHandle> LastMultiplierHandle;
	TSharedPtr<IPropertyHandle> BaseMultiplierHandle;
};

