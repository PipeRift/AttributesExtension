// Copyright 2015-2018 Piperift. All Rights Reserved.

#include "AttrModifier.h"
#include "FloatAttr.h"


void FAttrModifier::Apply(const FFloatAttr& Attribute, float& ActualValue) const {
    if (PercentageIncrement != 0.f) {
        ActualValue *= 1.f + (PercentageIncrement / 100.f);
    }

    if (BasePercentageIncrement != 0.f) {
        ActualValue += Attribute.GetBaseValue() * (BasePercentageIncrement / 100.f);
    }

    ActualValue += ScalarIncrement;
}