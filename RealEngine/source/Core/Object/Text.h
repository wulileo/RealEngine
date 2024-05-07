#pragma once

#include "Widget.h"
#include "Font.h"

class UText : public UWidget {
public:
    explicit UText(const String &Name) : UWidget(Name) {

    }

    void SetText(String InText);

    void Tick() override;

public:
    Font *Font{};
    String Text;
    bool dirty{};
    FVector4 Color;
};
