#include "Mesh.h"

Mesh *Mesh::load_mesh(const string &path) {
    std::ifstream stream(path, std::ios::in | std::ios::binary);

    MeshFileHead head{};
    stream.read((char *) &head, sizeof(MeshFileHead));

    auto *vertex_data = (unsigned char *) malloc(head.num * sizeof(Vertex));
    stream.read((char *) vertex_data, (int) (head.num * sizeof(Vertex)));

    auto *vertex_index_data = (unsigned short *) malloc(head.index_num * sizeof(unsigned short));
    stream.read((char *) vertex_index_data, (int) (head.index_num * sizeof(unsigned short)));

    stream.close();

    Mesh *mesh = new Mesh();
    mesh->vertex_num = head.num;
    mesh->vertex_index_num = head.index_num;
    mesh->vertex_data = (Vertex *) vertex_data;
    mesh->vertex_index_data = vertex_index_data;

    return mesh;
}
