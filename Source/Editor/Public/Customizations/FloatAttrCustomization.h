// Copyright 2015-2023 Piperift. All Rights Reserved.

#pragma once

#include <EditorUndoClient.h>
#include <IPropertyTypeCustomization.h>
#include <PropertyHandle.h>
#include <Widgets/Views/SListView.h>



class FFloatAttrCustomization : public IPropertyTypeCustomization, public FEditorUndoClient
{
public:
	virtual ~FFloatAttrCustomization();

	/**
	 * Creates a new instance.
	 *
	 * @return A new struct customization for Anchor Type.
	 */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FFloatAttrCustomization);
	}

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle,
		class FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle,
		class IDetailChildrenBuilder& StructBuilder,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils) override
	{}

protected:
	//~ Begin FEditorUndoClient Interface
	virtual void PostUndo(bool bSuccess) override
	{
		RefreshValue();
	}
	virtual void PostRedo(bool bSuccess) override
	{
		RefreshValue();
	}
	// End of FEditorUndoClient

	void RefreshValue();


	FSimpleDelegate BaseValueChanged;

	TSharedPtr<IPropertyHandle> BaseValueHandle;
	TSharedPtr<IPropertyHandle> ValueHandle;
};
