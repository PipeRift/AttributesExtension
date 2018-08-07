// Copyright 2015-2018 Piperift. All Rights Reserved.

#include "AttrCategory.h"
#include "AttributesSettings.h"
#include "AttributesModule.h"


const FAttrCategory FAttrCategory::NoCategory(NO_ATTRCATEGORY_NAME);

bool FAttrCategory::IsNone() const
{
	if (Name == NO_ATTRCATEGORY_NAME)
		return true;

	return !GetDefault<UAttributesSettings>()->GetCategories().Contains(Name);
}
