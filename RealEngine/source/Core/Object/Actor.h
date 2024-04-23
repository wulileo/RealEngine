#pragma once

#include "Object.h"
#include "Core/Collections/Array.h"
#include "Component.h"

class AComponent;

class AActor : public UObject {
private:
    TArray<AComponent *> Components;

public:
    AComponent *AddComponent(const String &Name);

};
