#include "World.h"

#include <glm/gtc/matrix_transform.hpp>

#include "core/object/MeshComponent.h"
#include "core/object/CameraComponent.h"
#include "core/input/Input.h"
#include "Font.h"
#include "application/Application.h"

void AWorld::BeginPlay() {
    AActor::BeginPlay();

    MousePos = Input::MousePosition;

    CreateCamera();

    CreatFont();

    CreateDragon();
}

void AWorld::Tick() {
    AActor::Tick();

    MainCameraComponent->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    MainCameraComponent->SetProjection(60.f, Screen::get_ratio(), 1.f, 10000.f);
    MainCameraComponent->Clear();

    if (Input::IsKeyHold(KEY_CODE_LEFT_ALT) && Input::IsMouseButtonHold(MOUSE_BUTTON_LEFT)) {
        float degrees = -(Input::MousePosition.x - MousePos.x);

        glm::mat4 old_mat4 = glm::mat4(1.0f);

        glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec4 old_pos = glm::vec4(MainCameraComponent->Transform.Position, 1.0f);
        glm::vec4 new_pos = rotate_mat4 * old_pos;

        MainCameraComponent->Transform.Position = glm::vec3(new_pos);
    }
    MousePos = Input::MousePosition;

    MainCameraComponent->Transform.Position = MainCameraComponent->Transform.Position * (float) (10 - Input::MouseRollNum) / 10.f;
}

void AWorld::CreateDragon() {
    auto Dragon = new AActor("Dragon");
    auto MeshComponent = Dragon->AddComponent<AMeshComponent>("Mesh");
    MeshComponent->LoadMesh(Utils::data_dir + "model/dragon.mesh");
    MeshComponent->LoadMaterial(Utils::data_dir + "material/dragon.mat");
}

void AWorld::CreatFont() const {
    vector<Vertex> vertex_vector = {
            {{-1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f,  -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{-1.0f, 1.0f,  1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };
    vector<unsigned short> index_vector = {
            0, 1, 2,
            0, 2, 3
    };
    auto FontActor = new AActor("Font");
    auto *MeshComponent = FontActor->AddComponent<AMeshComponent>("Mesh");
    MeshComponent->CreateMesh(vertex_vector, index_vector);
    MeshComponent->LoadMaterial(Utils::data_dir + "material/dragon.mat");
    Font *Font = Font::load_from_file(Utils::data_dir + "font/hkyuan.ttf", 500);
    Font->load_character('A');
    MeshComponent->MeshRenderer.material->set_texture("u_diffuse_texture", Font->font_texture);
}

void AWorld::CreateCamera() {
    MainCameraComponent = AddComponent<ACameraComponent>("Camera");
    MainCameraComponent->Transform.Position = glm::vec3(0, 0, 10);
    Application::MainCameraComponent = MainCameraComponent;
}

void AWorld::CreateCube() {
    auto Cube = new AActor("Cube");
    auto MeshComponent = Cube->AddComponent<AMeshComponent>("Mesh");
    MeshComponent->LoadMesh(Utils::data_dir + "model/cube.mesh");
    MeshComponent->LoadMaterial(Utils::data_dir + "material/cube.mat");
}
