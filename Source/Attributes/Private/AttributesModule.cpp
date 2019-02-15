// Copyright 2015-2019 Piperift. All Rights Reserved.

#include "AttributesModule.h"
#include "AttributesSettings.h"

DEFINE_LOG_CATEGORY(LogAttributes)

#define LOCTEXT_NAMESPACE "AttributesModule"

void FAttributesModule::StartupModule()
{
	UE_LOG(LogAttributes, Warning, TEXT("Attributes: Log Started"));

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	RegisterSettings();
}

void FAttributesModule::ShutdownModule()
{
	UE_LOG(LogAttributes, Warning, TEXT("Attributes: Log Ended"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

void FAttributesModule::RegisterSettings()
{
#if WITH_EDITOR
	// Registering some settings is just a matter of exposing the default UObject of
	// your desired class, feel free to add here all those settings you want to expose
	// to your LDs or artists.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Get Project Settings category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		// Register Attributes settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Game", "Attributes",
			LOCTEXT("RuntimeAttributesSettingsName", "Attributes"),
			LOCTEXT("RuntimeAttributesDescription", "Attributes configuration"),
			GetMutableDefault<UAttributesSettings>());

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FAttributesModule::HandleSettingsSaved);
		}
	}
#endif
}

void FAttributesModule::UnregisterSettings()
{
#if WITH_EDITOR
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Game", "Attributes");
	}
#endif
}

bool FAttributesModule::HandleSettingsSaved()
{
	UAttributesSettings* Settings = GetMutableDefault<UAttributesSettings>();
	bool ResaveSettings = false;

	if (ModifiedSettingsDelegate.IsBound()) {
		ModifiedSettingsDelegate.Execute();
	}

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAttributesModule, Attributes)