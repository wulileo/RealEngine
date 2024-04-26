#include "World.h"

#include <glm/gtc/matrix_transform.hpp>

#include "core/object/MeshComponent.h"
#include "core/object/CameraComponent.h"
#include "core/input/Input.h"

void AWorld::BeginPlay() {
    AActor::BeginPlay();

    Actor = new AActor();
    MeshComponent = Actor->AddComponent<AMeshComponent>();
    MeshComponent->LoadMesh(Utils::data_dir + "model/dragon.mesh");
    MeshComponent->LoadMaterial(Utils::data_dir + "material/dragon.mat");
//    MeshComponent->LoadMesh(Utils::data_dir + "model/cube.mesh");
//    MeshComponent->LoadMaterial(Utils::data_dir + "material/cube.mat");

    CameraComponent = Actor->AddComponent<ACameraComponent>();
    CameraComponent->Transform.Position = glm::vec3(0, 0, 10);

    MousePos = Input::MousePosition;
}

void AWorld::Tick() {
    AActor::Tick();

    CameraComponent->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    CameraComponent->SetProjection(60.f, Screen::get_ratio(), 1.f, 10000.f);
    CameraComponent->Clear();

    if (Input::IsKeyHold(KEY_CODE_R)) {
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.1f;
        glm::vec3 rotation = MeshComponent->Transform.Rotation;
        rotation.y = rotate_eulerAngle;
        MeshComponent->Transform.Rotation = rotation;
    }

    if (Input::IsKeyHold(KEY_CODE_LEFT_ALT) && Input::IsMouseButtonHold(MOUSE_BUTTON_LEFT)) {
        float degrees = -(Input::MousePosition.x - MousePos.x);

        glm::mat4 old_mat4 = glm::mat4(1.0f);

        glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec4 old_pos = glm::vec4(CameraComponent->Transform.Position, 1.0f);
        glm::vec4 new_pos = rotate_mat4 * old_pos;

        CameraComponent->Transform.Position = glm::vec3(new_pos);
    }
    MousePos = Input::MousePosition;

    CameraComponent->Transform.Position = CameraComponent->Transform.Position * (float) (10 - Input::MouseRollNum) / 10.f;
}
