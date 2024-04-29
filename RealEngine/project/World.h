#ifndef REALENGINE_WORLD_H
#define REALENGINE_WORLD_H

#include "core/object/Actor.h"
#include "core/object/MeshComponent.h"
#include "core/object/CameraComponent.h"
#include "application/Screen.h"

class AWorld : public AActor {
public:
    explicit AWorld(const String &Name) : AActor(Name) {

    }

    void BeginPlay() override;

    void Tick() override;

private:
    void CreateCamera();

    void CreateDragon();

    void CreatFont() const;

public:
    ACameraComponent *MainCameraComponent{};

    FVector2 MousePos;

    void CreateCube();
};

#endif //REALENGINE_WORLD_H
