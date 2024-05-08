#pragma once

#include "glad/glad.h"
#include "MovableComponent.h"

class ACameraComponent : public AMovableComponent {
public:
    explicit ACameraComponent(const String &Name) : AMovableComponent(Name) {

    }

    void SetView(const FVector &Forward, const FVector &Up);

    void SetProjection(float Degree, float Ratio, float NearClip, float FarClip);

    void Clear() const;

    void SetOrthographic(float left, float right, float bottom, float top, float z_near, float z_far);

    void OnAddToOwner() override;

    void SetDepth(int Depth);

public:
    static TArray<ACameraComponent *> CameraComponentArray;

    FQuad View;
    FQuad Projection;
    FVector4 ClearColor{49.f / 255, 77.f / 255, 121.f / 255, 1.f};
    unsigned int ClearFlag{GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT};

    int Mask{0x00};
    int Depth{0};

    static void Sort();
};
