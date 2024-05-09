#pragma once

#include "core/Global.h"
#include "core/collections/Array.h"

class AComponent;

class AMovableComponent;

class AActor;

class UWidget;

class UObject {
public:
    UObject() = delete;

    explicit UObject(const String &InName) {
        this->Name = InName;
    }

    AComponent *AddComponent(const String &InName) {
        auto *Component = Create<AComponent>(InName);
        if (Component) {
            OnAddComponent(Component);
            return Component;
        }
        return nullptr;
    }

    template<typename T>
    T *AddComponent(const String &InName) {
        T *t = new T(InName);
        auto *Component = Cast<AComponent *>(t);
        if (Component) {
            OnAddComponent(Component);
            return t;
        }
        return nullptr;
    }

    TArray<AComponent *> GetComponents() {
        TArray<AComponent *> Result;
        for (auto Component: Components) {
            Result.Add(Component);
        }
        return Result;
    }

    template<typename T>
    TArray<T *> GetComponents() {
        TArray<T *> Result;
        for (auto Component: Components) {
            T *t = Cast<T *>(Component);
            if (t) {
                Result.Add(t);
            }
        }
        return Result;
    }

    void OnAddComponent(AComponent *Component);

    void SetRootComponent(AComponent *Component);

    void SetTransform(const FTransform &Transform) const;

    void SetLocation(const FVector &Location) const;

    void SetRotation(const FVector &Rotation) const;

    void SetScale(const FVector &Scale) const;

    virtual void BeginPlay();

    virtual void Tick();

private:
    TArray<AComponent *> Components;

public:
    static TArray<UObject *> Objects;

    String Name;
    int Layer{0x00};

    AMovableComponent *RootComponent{};
};
