#pragma once

#include <utility>

#include "Mesh.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Component.h"
#include "MovableComponent.h"

class AMeshComponent : public AMovableComponent {
public:
    explicit AMeshComponent(const String &Name) : AMovableComponent(Name) {

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

    MeshRenderer MeshRenderer;

    void CreateMesh(const vector<Vertex> &data, const vector<unsigned short> &index_data);
};