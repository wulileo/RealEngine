#include "Actor.h"

AComponent *AActor::AddComponent(const String &Name) {
    auto *Component = Create<AComponent>(Name);
    Component->Owner = this;
    Components.Add(Component);
    return Component;
}

void AActor::BeginPlay() {

}

void AActor::Tick() {
    for (auto Component: Components) {
        Component->Tick();
    }
}
