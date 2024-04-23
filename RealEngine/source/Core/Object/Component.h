#pragma once

#include "Object.h"
#include "Actor.h"

class AActor;

class AComponent : public UObject {
public:
    AActor *Owner = NULL;
};
