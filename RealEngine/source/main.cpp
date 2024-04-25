#define GLFW_INCLUDE_NONE

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "glfw3.h"
#include "glm.hpp"

#include "Utils.h"

#include "Core/Object/MeshComponent.h"
#include "Core/Object/Actor.h"
#include "Core/Object/CameraComponent.h"
#include "Core/Input/Input.h"
#include "gtc/matrix_transform.hpp"

static void error_callback(const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Input::RecordKey(key, action);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    Input::RecordKey(button, action);
}

void mouse_move_callback(GLFWwindow *window, double x, double y) {
    Input::MousePosition = {x, y};
}

void mouse_scroll_callback(GLFWwindow *window, double x, double y) {
    Input::RecordScroll(y);
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

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
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

    auto *Camera = new AActor();
    auto CameraComponent = Camera->AddComponent<ACameraComponent>();
    CameraComponent->Transform.Position = glm::vec3(0, 0, 10);

    glm::vec2 last_frame_mouse_position = Input::MousePosition;

    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float) width / (float) height;

        glViewport(0, 0, width, height);

        CameraComponent->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        CameraComponent->SetProjection(60.f, ratio, 1.f, 1000.f);
        CameraComponent->Clear();

        if (Input::IsKeyHold(KEY_CODE_R)) {
            static float rotate_eulerAngle = 0.f;
            rotate_eulerAngle += 0.1f;
            glm::vec3 rotation = MeshComponent->Transform.Rotation;
            rotation.y = rotate_eulerAngle;
            MeshComponent->Transform.Rotation = rotation;
        }

        if (Input::IsKeyHold(KEY_CODE_LEFT_ALT) && Input::IsMouseButtonHold(MOUSE_BUTTON_LEFT)) {
            float degrees = -(Input::MousePosition.x - last_frame_mouse_position.x);

            glm::mat4 old_mat4 = glm::mat4(1.0f);

            glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec4 old_pos = glm::vec4(CameraComponent->Transform.Position, 1.0f);
            glm::vec4 new_pos = rotate_mat4 * old_pos;

            CameraComponent->Transform.Position = glm::vec3(new_pos);
        }
        last_frame_mouse_position = Input::MousePosition;

        CameraComponent->Transform.Position = CameraComponent->Transform.Position * (float) (10 - Input::MouseRollNum) / 10.f;

        Input::Update();

        MeshComponent->Render(CameraComponent->View, CameraComponent->Projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}