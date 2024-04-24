#include "MeshComponent.h"

CLASS(AMeshComponent)
    PROPERTY(AMeshComponent, Transform)
CLASS_END

void AMeshComponent::LoadMesh(const String &MeshFile) {
    MeshRenderer.mesh = Mesh::load_mesh(MeshFile);
}

void AMeshComponent::LoadMaterial(const String &MaterialFile) {
    MeshRenderer.material = Material::parse(MaterialFile);
}

void AMeshComponent::Render(FQuad View, FQuad Projection) {
    MeshRenderer.render(Transform.Position, Transform.Rotation, Transform.Scale, Projection, View);
}
