#include "Object.h"

#include "Component.h"
#include "MovableComponent.h"

TArray<UObject *> UObject::Objects;

void UObject::BeginPlay() {

}

void UObject::Tick() {
    for (auto Component: Components) {
        Component->Tick();
    }
}

void UObject::OnAddComponent(AComponent *Component) {
    if (!RootComponent && Cast<AMovableComponent *>(Component)) {
        RootComponent = Cast<AMovableComponent *>(Component);
    }

    Components.Add(Component);
    Component->Owner = this;
    Component->OnAddToOwner();
}

void UObject::SetRootComponent(AComponent *Component) {
    if (Cast<AMovableComponent *>(Component)) {
        RootComponent = Cast<AMovableComponent *>(Component);
    }
}

void UObject::SetTransform(const FTransform &Transform) const {
    if (!RootComponent) {
        return;
    }
    RootComponent->Transform.Position = Transform.Position;
    RootComponent->Transform.Rotation = Transform.Rotation;
    RootComponent->Transform.Scale = Transform.Scale;
}

void UObject::SetLocation(const FVector &Location) const {
    if (!RootComponent) {
        return;
    }
    RootComponent->Transform.Position = Location;
}

void UObject::SetRotation(const FVector &Rotation) const {
    if (!RootComponent) {
        return;
    }
    RootComponent->Transform.Rotation = Rotation;
}

void UObject::SetScale(const FVector &Scale) const {
    if (!RootComponent) {
        return;
    }
    RootComponent->Transform.Scale = Scale;
}
