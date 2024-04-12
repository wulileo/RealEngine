#ifndef UNTITLED_VERTEXDATA_H
#define UNTITLED_VERTEXDATA_H

#include <vector>
#include <glm/glm.hpp>

using std::vector;

struct Vertex {
    glm::vec3 pos;
    glm::vec4 color;
    glm::vec2 uv;
};

static const Vertex kVertexes[36] = {
        //Front
        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),

        //back
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),

        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),


        //left
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),

        glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),

        //right
        glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),

        glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),

        //up
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),

        //down
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f),
};

static vector<Vertex> kVertexRemoveDuplicateVector;

static vector<unsigned short> kVertexIndexVector;

static void VertexRemoveDuplicate() {
    for (const Vertex &vertex: kVertexes) {
        int index = -1;
        for (int j = 0; j < kVertexRemoveDuplicateVector.size(); ++j) {
            if (vertex.pos == kVertexRemoveDuplicateVector[j].pos &&
                vertex.color == kVertexRemoveDuplicateVector[j].color &&
                vertex.uv == kVertexRemoveDuplicateVector[j].uv) {
                index = j;
                break;
            }
        }
        if (index < 0) {
            kVertexRemoveDuplicateVector.push_back(vertex);
            kVertexIndexVector.push_back(kVertexRemoveDuplicateVector.size() - 1);
        }
        else {
            kVertexIndexVector.push_back(index);
        }
    }
}

#endif //UNTITLED_VERTEXDATA_H