#pragma once
#include "SlateBasics.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"

#include "AttrCategory.h"
#include "Private/Customizations/AttrCategoryPin.h"
 
class FAttrCategoryPinFactory : public FGraphPanelPinFactory
{
    virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;
};
