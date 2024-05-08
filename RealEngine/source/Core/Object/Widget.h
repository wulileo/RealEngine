#pragma once

#include "Object.h"

class UWidget : public UObject {
public:
    explicit UWidget(const String &Name) : UObject(Name) {
        UObject::Objects.Add(this);
        this->Layer = 0x02;
    }
};
