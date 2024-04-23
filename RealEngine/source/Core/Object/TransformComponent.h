#pragma once

#include "Component.h"

class ATransformComponent : public AComponent {
public:
    FVector Position;
    FVector Rotation;
    FVector Scale;
};

CLASS(ATransformComponent)
PROPERTY(ATransformComponent, Position)
PROPERTY(ATransformComponent, Rotation)
PROPERTY(ATransformComponent, Scale)
CLASS_END