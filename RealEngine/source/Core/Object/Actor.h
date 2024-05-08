#pragma once

#include "Object.h"

class AActor : public UObject {
public:
    explicit AActor(const String &Name) : UObject(Name) {
        UObject::Objects.Add(this);
    }
};
