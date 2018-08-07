// Copyright 2015-2018 Piperift. All Rights Reserved.

#include "AttrCategoryPinFactory.h"


TSharedPtr<class SGraphPin> FAttrCategoryPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	if (InPin->PinType.PinCategory == K2Schema->PC_Struct &&
		InPin->PinType.PinSubCategoryObject == FAttrCategory::StaticStruct() &&
		!InPin->PinType.bIsReference)
	{
		return SNew(SAttrCategoryPin, InPin); //and return our customized pin widget ;).
	}
	return nullptr;
}