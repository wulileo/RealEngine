#pragma once

#include "Object.h"

class AComponent : public UObject {
public:
    explicit AComponent(const String &Name) : UObject(Name) {

    }

    void Tick() override {};

    virtual void OnAddToOwner() {};

public:
    UObject *Owner{};
};
