#include "CameraComponent.h"
#include "gtc/matrix_transform.hpp"

void ACameraComponent::SetView(const FVector &Forward, const FVector &Up) {
    View = glm::lookAt(Transform.Position, Forward, Up);
}

void ACameraComponent::SetProjection(float Degree, float Ratio, float NearClip, float FarClip) {
    Projection = glm::perspective(glm::radians(Degree), Ratio, NearClip, FarClip);
}

void ACameraComponent::Clear() const {
    glClear(ClearFlag);
    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
}
