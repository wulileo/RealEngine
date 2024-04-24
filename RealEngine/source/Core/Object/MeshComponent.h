#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshRenderer.h"

class AMeshComponent : public AComponent {
public:
    void LoadMesh(const String &MeshFile);

    void LoadMaterial(const String &MaterialFile);

    void Render(FQuad View, FQuad Projection);

private:

public:
    FTransform Transform;

private:
    MeshRenderer MeshRenderer;
};