#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshRenderer.h"

class AMeshComponent : public AComponent {
public:
    explicit AMeshComponent(const String &Name) : AComponent(Name) {

    }

    void LoadMesh(const String &MeshFile);

    void LoadMaterial(const String &MaterialFile);

    void Render(FQuad View, FQuad Projection);

private:

public:
    FTransform Transform;

    MeshRenderer MeshRenderer;

    void CreateMesh(const vector<Vertex> &data, const vector<unsigned short> &index_data);
};