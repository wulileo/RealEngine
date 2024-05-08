#pragma once

#include "Component.h"

class AMovableComponent : public AComponent {
public:
    explicit AMovableComponent(const String &Name) : AComponent(Name) {

    }

public:
    FTransform Transform;
};
