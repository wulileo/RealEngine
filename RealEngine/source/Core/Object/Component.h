#pragma once

#include "Object.h"
#include "Actor.h"

class AActor;

class AComponent : public UObject {
public:
    explicit AComponent(const String &Name) : UObject(Name) {

    }

    virtual void Tick();

public:
    AActor *Owner = NULL;
};
