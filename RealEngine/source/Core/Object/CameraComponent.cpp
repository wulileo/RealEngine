#include "CameraComponent.h"
#include "gtc/matrix_transform.hpp"

TArray<ACameraComponent *> ACameraComponent::CameraComponentArray;

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

void ACameraComponent::SetOrthographic(float left, float right, float bottom, float top, float z_near, float z_far) {
    Projection = glm::ortho(left, right, bottom, top, z_near, z_far);
}

void ACameraComponent::OnAddToOwner() {
    AComponent::OnAddToOwner();

    CameraComponentArray.Add(this);
}

void ACameraComponent::SetDepth(int InDepth) {
    this->Depth = InDepth;

    Sort();
}

void ACameraComponent::Sort() {
    CameraComponentArray.Sort([](ACameraComponent *A, ACameraComponent *B) {
        return A->Depth < B->Depth;
    });
}
