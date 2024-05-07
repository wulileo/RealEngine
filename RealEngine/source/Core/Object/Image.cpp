#include "Image.h"

#include "Texture2D.h"
#include "Mesh.h"
#include "MeshComponent.h"

void UImage::Tick() {
    UWidget::Tick();

    if (!Texture2D) {
        return;
    }
    vector<Vertex> vertex_vector = {
            {{0.f,              0.0f,              0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.f, 0.f}},
            {{Texture2D->width, 0.0f,              0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.f, 0.f}},
            {{Texture2D->width, Texture2D->height, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.f, 1.f}},
            {{0.f,              Texture2D->height, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.f, 1.f}}
    };
    vector<unsigned short> index_vector = {
            0, 1, 2,
            0, 2, 3
    };

    auto MeshComponent = AddComponent<AMeshComponent>("Mesh");
    MeshComponent->CreateMesh(vertex_vector, index_vector);
    MeshComponent->LoadMaterial(Utils::data_dir + "material/ui_image.mat");

    MeshComponent->MeshRenderer.material->set_texture("u_diffuse_texture", Texture2D);
}
