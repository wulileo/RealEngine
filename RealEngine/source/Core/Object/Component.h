#pragma once

#include "Object.h"
#include "Actor.h"

class AActor;

class AComponent : public UObject {
public:
    virtual void Tick();

public:
    AActor *Owner = NULL;
};
