#pragma once

#include "Widget.h"
#include "Texture2D.h"

class UImage : public UWidget {
public:
    explicit UImage(const String &Name) : UWidget(Name) {

    }

    void Tick() override;

public:
    Texture2D *Texture2D = nullptr;
};
