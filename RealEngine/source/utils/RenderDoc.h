#pragma once

#include "renderdoc_app.h"

class RenderDoc {
public:
    static void init();

    static void start();

    static void end();

public:
    static RENDERDOC_API_1_4_1 *rdoc_api;
};
