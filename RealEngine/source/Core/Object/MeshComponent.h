#pragma once

#include "Component.h"

#include <utility>
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

    void SetPreRenderFunc(std::function<void()> Func) {
        PreRenderFunc = std::move(Func);
    }

    void SetPostRenderFunc(std::function<void()> Func) {
        PostRenderFunc = std::move(Func);
    }

private:

public:
    std::function<void()> PreRenderFunc;

    std::function<void()> PostRenderFunc;

    FTransform Transform;

    MeshRenderer MeshRenderer;

    void CreateMesh(const vector<Vertex> &data, const vector<unsigned short> &index_data);
};