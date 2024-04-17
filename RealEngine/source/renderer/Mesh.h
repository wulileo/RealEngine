#ifndef REALENGINE_MESH_H
#define REALENGINE_MESH_H

#include <string>
#include <fstream>
#include <iostream>

#include "glm.hpp"

using std::string;

struct Vertex {
    glm::vec3 pos;
    glm::vec4 color;
    glm::vec2 uv;
};

struct MeshFileHead {
    char type[4];
    int num;
    int index_num;
};

class Mesh {
public:
    int vertex_num;
    int vertex_index_num;
    Vertex *vertex_data;
    unsigned short *vertex_index_data;

public:
    static Mesh *load_mesh(const string &path);
};


#endif //REALENGINE_MESH_H
