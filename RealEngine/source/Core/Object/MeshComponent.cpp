#include "MeshComponent.h"

CLASS(AMeshComponent)
    CONSTRUCTOR(String)
            PROPERTY(AMeshComponent, Transform)CLASS_END

void AMeshComponent::LoadMesh(const String &MeshFile) {
    MeshRenderer.mesh = Mesh::load_mesh(MeshFile);
}

void AMeshComponent::LoadMaterial(const String &MaterialFile) {
    MeshRenderer.material = Material::parse(MaterialFile);
}

void AMeshComponent::Render(FQuad View, FQuad Projection) {
    MeshRenderer.render(Transform.Position, Transform.Rotation, Transform.Scale, Projection, View, PreRenderFunc, PostRenderFunc);
}

void AMeshComponent::CreateMesh(const vector<Vertex> &data, const vector<unsigned short> &index_data) {
    MeshRenderer.mesh = new Mesh();
    MeshRenderer.mesh->vertex_num = (int) data.size();
    MeshRenderer.mesh->vertex_index_num = (int) index_data.size();

    unsigned short vertex_data_size = MeshRenderer.mesh->vertex_num * sizeof(Vertex);
    MeshRenderer.mesh->vertex_data = static_cast<Vertex *>(malloc(vertex_data_size));
    memcpy(MeshRenderer.mesh->vertex_data, &data[0], vertex_data_size);

    unsigned short vertex_index_data_size = MeshRenderer.mesh->vertex_num * sizeof(Vertex);
    MeshRenderer.mesh->vertex_index_data = static_cast<unsigned short *>(malloc(vertex_index_data_size));
    memcpy(MeshRenderer.mesh->vertex_index_data, &index_data[0], vertex_index_data_size);
}
