#define GLFW_INCLUDE_NONE

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Utils.h"

#include "Core/Object/MeshComponent.h"
#include "Core/Object/Actor.h"

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

//    Texture2D::Compress("../data/images/dragon.png", "../data/images/dragon.ret");
//
//    return 0;

    auto *Actor = new AActor();
    auto MeshComponent = Actor->AddComponent<AMeshComponent>();
    MeshComponent->LoadMesh(Utils::data_dir + "model/dragon.mesh");
    MeshComponent->LoadMaterial(Utils::data_dir + "material/dragon.mat");

    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float) width / (float) height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.1f;
        glm::vec3 rotation = MeshComponent->Transform.Rotation;
        rotation.y = rotate_eulerAngle;
        MeshComponent->Transform.Rotation = rotation;

        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        MeshComponent->Render(view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}