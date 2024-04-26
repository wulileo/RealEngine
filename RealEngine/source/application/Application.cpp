#include "Application.h"

#include "core/object/Actor.h"
#include "core/input/Input.h"
#include "core/object/MeshComponent.h"
#include "core/object/CameraComponent.h"

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

void Application::init_opengl() {
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

void Application::tick() const {
    update_screen();

    for (auto Actor: UObject::Actors) {
        Actor->Tick();
    }

    Input::Update();
}

void Application::update_screen() const {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    Screen::set_width_height(width, height);
}

void Application::render() {
    for (auto Actor: UObject::Actors) {
        TArray<AMeshComponent *> MeshComponents;
        Actor->GetComponents<AMeshComponent>(MeshComponents);

        TArray<ACameraComponent *> CameraComponents;
        Actor->GetComponents<ACameraComponent>(CameraComponents);

        if (MeshComponents.Size() > 0 && CameraComponents.Size() > 0) {
            AMeshComponent *MeshComponent = MeshComponents.Get(0);
            ACameraComponent *CameraComponent = CameraComponents.Get(0);
            MeshComponent->Render(CameraComponent->View, CameraComponent->Projection);
        }
    }
}

void Application::run() const {
    while (!glfwWindowShouldClose(window)) {
        tick();

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
