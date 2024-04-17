#define GLFW_INCLUDE_NONE

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform2.hpp"
#include "gtx/euler_angles.hpp"

#include "Texture2D.h"
#include "Mesh.h"
#include "Shader.h"

static void error_callback(const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow *window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location, u_diffuse_texture_location, a_uv_location;
Texture2D *texture2d = nullptr;
GLuint kVBO, kEBO;
GLuint kVAO;
Mesh *mesh;

void init_opengl() {
    glfwSetErrorCallback(reinterpret_cast<GLFWerrorfun>(error_callback));

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(960, 640, "RealEngine", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
}

void generate_buffer_object() {
    glGenBuffers(1, &kVBO);
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    glBufferData(GL_ARRAY_BUFFER, (long) (mesh->vertex_num * sizeof(Vertex)), mesh->vertex_data, GL_STATIC_DRAW);

    glGenBuffers(1, &kEBO);
    glBindBuffer(GL_ARRAY_BUFFER, kEBO);
    glBufferData(GL_ARRAY_BUFFER, (long) (mesh->vertex_index_num * sizeof(unsigned short)), mesh->vertex_index_data,
                 GL_STATIC_DRAW);

    glBindVertexArray(kVAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, kVBO);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(Vertex), (void *) (sizeof(float) * 3));
        glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(Vertex), (void *) (sizeof(float) * (3 + 4)));
        glEnableVertexAttribArray(vpos_location);
        glEnableVertexAttribArray(vcol_location);
        glEnableVertexAttribArray(a_uv_location);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void generate_vertex_array_object() {
    glGenVertexArrays(1, &kVAO);
}

void createTexture(std::string path) {
    texture2d = Texture2D::Load(path);
}

int main() {

    mesh = Mesh::load_mesh("../../data/model/cube.mesh");

    init_opengl();

    createTexture("../../data/images/urban.ret");

    Shader *shader = Shader::find("../../data/shader/unlit");

    mvp_location = glGetUniformLocation(shader->program_id, "u_mvp");
    vpos_location = glGetAttribLocation(shader->program_id, "a_pos");
    vcol_location = glGetAttribLocation(shader->program_id, "a_color");
    a_uv_location = glGetAttribLocation(shader->program_id, "a_uv");

    u_diffuse_texture_location = glGetUniformLocation(shader->program_id, "u_diffuse_texture");

    generate_vertex_array_object();
    generate_buffer_object();

    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float) width / (float) height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0));

        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle),
                                                glm::radians(rotate_eulerAngle),
                                                glm::radians(rotate_eulerAngle));

        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
        model = trans * scale * rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;

        glUseProgram(shader->program_id);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);

            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture2d->id);
            glUniform1i(u_diffuse_texture_location, 0);

            glBindVertexArray(kVAO);
            {
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
            }
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}