#pragma once

#include "SlateBasics.h"
#include "StringEnumPin.h"


class SAttrCategoryPin : public SStringEnumPin
{
public:
    SLATE_BEGIN_ARGS(SAttrCategoryPin) {}
    SLATE_END_ARGS()

public:
    void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

    //Display slate widget used for customization.
    virtual TSharedRef<SWidget> GetDefaultValueWidget() override;

private:
    void ParseDefaultValue();
    void ApplyDefaultValue();

protected:
    FName DefaultNameValue;

    /** Returns all the enum items.
    * This is for override purposes.
    */
    virtual void GetEnumItems(TArray<FString>& Values);

    /** Called when selection changed.
    * This is for override purposes.
    */
    virtual void OnItemSelected(FString Value);

    /** Returns the actually selected item.
    * This is for override purposes.
    */
    virtual FText GetSelectedItem() const;
};