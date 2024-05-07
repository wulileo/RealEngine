#pragma once

#include "Object.h"
#include "CameraComponent.h"

class UWidget : public UObject {
public:
    explicit UWidget(const String &Name) : UObject(Name) {
        UObject::Widgets.Add(this);
        this->Layer = 0x02;
    }

    AComponent *AddComponent(const String &Name);

    template<typename T>
    T *AddComponent(const String &Name) {
        T *t = new T(Name);
        auto *Component = Cast<AComponent *>(t);
        if (Component) {
            Component->Owner = this;
            Components.Add(Component);
            Component->OnAddToOwner();
            return t;
        }
        return nullptr;
    }

    void GetComponents(TArray<AComponent *> &Out) {
        for (auto Component: Components) {
            Out.Add(Component);
        }
    }

    template<typename T>
    void GetComponents(TArray<T *> &Out) {
        for (auto Component: Components) {
            T *t = Cast<T *>(Component);
            if (t) {
                Out.Add(t);
            }
        }
    }

    virtual void BeginPlay();

    virtual void Tick();

private:
    TArray<AComponent *> Components;
};
