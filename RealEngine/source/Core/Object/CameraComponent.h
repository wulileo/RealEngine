#pragma once

#include "glad/glad.h"
#include "Component.h"

class ACameraComponent : public AComponent {
public:
    void SetView(const FVector &Forward, const FVector &Up);

    void SetProjection(float Degree, float Ratio, float NearClip, float FarClip);

    void Clear() const;

public:
    FTransform Transform;

    FQuad View;
    FQuad Projection;
    FVector4 ClearColor{49.f / 255, 77.f / 255, 121.f / 255, 1.f};
    unsigned int ClearFlag{GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT};
};
