// Copyright 2015-2023 Piperift. All Rights Reserved.

#pragma once

#include "EdGraphUtilities.h"
#include "IAssetTools.h"
#include "PropertyEditorModule.h"


DECLARE_LOG_CATEGORY_EXTERN(LogAttributesEd, All, All)

class FAttributesEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


private:
	void RegisterPropertyTypeCustomizations();

	/**
	 * Registers a custom struct
	 *
	 * @param StructName                The name of the struct to register for property customization
	 * @param StructLayoutDelegate    The delegate to call to get the custom detail layout instance
	 */
	void RegisterCustomPropertyTypeLayout(
		FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate);

	template <class T>
	void RegisterCustomPinFactory();

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);
		CreatedAssetTypeActions.Add(Action);
	}


	/** All created pin factories.  Cached here so that we can unregister them during shutdown. */
	TArray<TSharedPtr<FGraphPanelPinFactory> > CreatedPinFactories;
	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray<TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
};