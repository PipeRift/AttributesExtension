// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <Modules/ModuleManager.h>

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#endif //WITH_EDITOR


DECLARE_LOG_CATEGORY_EXTERN(LogAttributes, All, All);

class FAttributesModule : public IModuleInterface
{
public:

    // Get Attributes module instance
    FORCEINLINE static FAttributesModule& Get() {
        return FModuleManager::LoadModuleChecked<FAttributesModule>("Attributes");
    }

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    virtual bool SupportsDynamicReloading() override { return true; }

    DECLARE_DELEGATE_RetVal(void, FOnModifiedSettings)
    FOnModifiedSettings& OnModifiedSettings()
    {
        return ModifiedSettingsDelegate;
    }

private:
    /** Holds a delegate that is executed after the settings section has been modified. */
    FOnModifiedSettings ModifiedSettingsDelegate;

    void RegisterSettings();
    void UnregisterSettings();

    // Callbacks for when the settings were saved.
    bool HandleSettingsSaved();
};