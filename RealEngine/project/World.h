#ifndef REALENGINE_WORLD_H
#define REALENGINE_WORLD_H

#include "core/object/Actor.h"
#include "core/object/MeshComponent.h"
#include "core/object/CameraComponent.h"
#include "application/Screen.h"

class AWorld : public AActor {
public:
    void BeginPlay() override;

    void Tick() override;

public:
    AActor *Actor;
    AMeshComponent *MeshComponent;
    ACameraComponent *CameraComponent;
    FVector2 MousePos;
};

#endif //REALENGINE_WORLD_H
