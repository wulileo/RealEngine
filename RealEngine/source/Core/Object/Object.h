#pragma once

#include "core/Global.h"
#include "core/collections/Array.h"

class AActor;

class UWidget;

class UObject {
public:
    UObject() = delete;

    explicit UObject(const String &Name) {
        this->Name = Name;
    }

public:
    static TArray<AActor *> Actors;
    static TArray<UWidget *> Widgets;

    String Name;
    int Layer{0x00};
};
