#pragma once

#include "Object.h"
#include "Core/Collections/Map.h"
#include "Component.h"
#include "Core/Collections/Array.h"

class AComponent;

class AActor : public UObject {
public:
    AComponent *AddComponent(const String &Name);

    template<typename T>
    T *AddComponent() {
        T *t = new T();
        auto *Component = Cast<AComponent *>(t);
        if (Component) {
            Component->Owner = this;
            Components.Add(Component);
            return t;
        }
        return nullptr;
    }

private:
    TArray<AComponent *> Components;
};
