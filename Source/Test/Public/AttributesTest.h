// Copyright 2015-2019 Piperift. All Rights Reserved.

#pragma once

#include <Modules/ModuleManager.h>


class FAttributesTest : public IModuleInterface
{
public:

	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}

	static inline FAttributesTest& Get() {
		return FModuleManager::LoadModuleChecked<FAttributesTest>("AttributesTest");
	}

	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("AttributesTest");
	}
};

IMPLEMENT_MODULE(FAttributesTest, AttributesTest);
