#pragma once

#include "Widget.h"

class UMask : public UWidget {
public:
    explicit UMask(const String &Name) : UWidget(Name) {

    }

    void LoadImage(const String& path);
};
