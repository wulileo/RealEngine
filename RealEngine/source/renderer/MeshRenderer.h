#ifndef REALENGINE_MESHRENDERER_H
#define REALENGINE_MESHRENDERER_H

#include "glm.hpp"
#include "glad.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Shader.h"

class Material;

class Mesh;

class Texture2D;

class MeshRenderer {
public:
    Material *material{};
    Mesh *mesh{};

    unsigned int vertex_buffer_object = 0;
    unsigned int element_buffer_object = 0;
    unsigned int vertex_array_object = 0;

public:
    void render(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::mat4 projection, glm::mat4 view);
};


#endif //REALENGINE_MESHRENDERER_H
