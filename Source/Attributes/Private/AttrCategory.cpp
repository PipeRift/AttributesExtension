// Copyright 2015-2023 Piperift. All Rights Reserved.

#include "AttrCategory.h"

#include "AttributesModule.h"
#include "AttributesSettings.h"


const FAttrCategory FAttrCategory::NoCategory{NAME_None};

bool FAttrCategory::IsNone() const
{
	if (Name.IsNone())
		return true;

	return !GetDefault<UAttributesSettings>()->GetCategories().Contains(Name);
}
