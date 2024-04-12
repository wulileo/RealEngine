#include <iostream>
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <cstdlib>
#include <cstdio>

#include "VertexData.h"
#include "ShaderSource.h"
#include "Texture2D.h"

static void error_callback(const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow *window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location, u_diffuse_texture_location, a_uv_location;
Texture2D *texture2d = nullptr;
GLuint kVBO, kEBO;
GLuint kVAO;

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

void compile_shader() {
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader);
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader, sizeof(message), nullptr, message);
        std::cout << "compile vs error:" << message << std::endl;
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
    glCompileShader(fragment_shader);
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader, sizeof(message), nullptr, message);
        std::cout << "compile fs error:" << message << std::endl;
    }


    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    GLint link_status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        GLchar message[256];
        glGetProgramInfoLog(program, sizeof(message), nullptr, message);
        std::cout << "link error:" << message << std::endl;
    }
}

void generate_buffer_object() {
    glGenBuffers(1, &kVBO);
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    glBufferData(GL_ARRAY_BUFFER, (long) (kVertexRemoveDuplicateVector.size() * sizeof(Vertex)),
                 &kVertexRemoveDuplicateVector[0], GL_STATIC_DRAW);

    glGenBuffers(1, &kEBO);
    glBindBuffer(GL_ARRAY_BUFFER, kEBO);
    glBufferData(GL_ARRAY_BUFFER, (long) (kVertexIndexVector.size() * sizeof(unsigned short)),
                 &kVertexIndexVector[0], GL_STATIC_DRAW);

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

    VertexRemoveDuplicate();

    init_opengl();

    createTexture("../../resource/images/urban.ret");

    compile_shader();

    mvp_location = glGetUniformLocation(program, "u_mvp");
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");
    a_uv_location = glGetAttribLocation(program, "a_uv");

    u_diffuse_texture_location = glGetUniformLocation(program, "u_diffuse_texture");

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

        glUseProgram(program);
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