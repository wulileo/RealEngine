#pragma once

#include "Widget.h"
#include "Image.h"

class UButton : public UWidget {
public:
    explicit UButton(const String &Name) : UWidget(Name) {

    }

    void Tick() override;

public:
    UImage *ImageNormal{};
    UImage *ImagePress{};
    bool bPressed{};
    std::function<void()> ClickCallback;
};
