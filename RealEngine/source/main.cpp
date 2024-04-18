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

#include "Mesh.h"
#include "Material.h"
#include "Utils.h"
#include "MeshRenderer.h"

static void error_callback(const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow *window;

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

int main() {
    Utils::data_dir = "../data/";

    init_opengl();

    auto mesh = Mesh::load_mesh(Utils::data_dir + "model/cube.mesh");

    auto *material = Material::parse(Utils::data_dir + "material/cube.mat");

    auto *renderer = new MeshRenderer();
    renderer->mesh = mesh;
    renderer->material = material;

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

        renderer->mvp = mvp;
        renderer->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}