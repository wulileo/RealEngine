#include "MeshRenderer.h"
#include "gtx/transform.hpp"
#include "gtx/euler_angles.hpp"

void MeshRenderer::render(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::mat4 projection, glm::mat4 view) {
    glm::mat4 translation4 = glm::translate(position);
    glm::mat4 rotation4 = glm::eulerAngleYXZ(glm::radians(rotation.y),
                                             glm::radians(rotation.x),
                                             glm::radians(rotation.z));
    glm::mat4 scale4 = glm::scale(scale);
    glm::mat4 model = translation4 * scale4 * rotation4;
    glm::mat4 mvp = projection * view * model;

    GLuint program_id = material->shader->program_id;

    if (vertex_array_object == 0) {
        GLint pos_location = glGetAttribLocation(program_id, "a_pos");
        GLint col_location = glGetAttribLocation(program_id, "a_color");
        GLint uv_location = glGetAttribLocation(program_id, "a_uv");

        glGenBuffers(1, &vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, (int) (mesh->vertex_num * sizeof(Vertex)), mesh->vertex_data, GL_STATIC_DRAW);

        glGenBuffers(1, &element_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int) (mesh->vertex_index_num * sizeof(unsigned short)),
                     mesh->vertex_index_data, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vertex_array_object);

        glBindVertexArray(vertex_array_object);
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertex_array_object);
            glVertexAttribPointer(pos_location, 3, GL_FLOAT, false, sizeof(Vertex), 0);
            glVertexAttribPointer(col_location, 4, GL_FLOAT, false, sizeof(Vertex), (void *) (sizeof(float) * 3));
            glVertexAttribPointer(uv_location, 2, GL_FLOAT, false, sizeof(Vertex), (void *) (sizeof(float) * (3 + 4)));

            glEnableVertexAttribArray(pos_location);
            glEnableVertexAttribArray(col_location);
            glEnableVertexAttribArray(uv_location);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glUseProgram(program_id);
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glUniformMatrix4fv(glGetUniformLocation(program_id, "u_mvp"), 1, GL_FALSE, &mvp[0][0]);

        vector<pair<string, Texture2D *>> textures = material->textures;
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            GLint u_texture_location = glGetUniformLocation(program_id, textures[texture_index].first.c_str());
            glActiveTexture(GL_TEXTURE0 + texture_index);
            glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->id);
            glUniform1i(u_texture_location, texture_index);
        }

        glBindVertexArray(vertex_array_object);
        {
            glDrawElements(GL_TRIANGLES, mesh->vertex_index_num, GL_UNSIGNED_SHORT, 0);
        }
        glBindVertexArray(0);
    }
}
