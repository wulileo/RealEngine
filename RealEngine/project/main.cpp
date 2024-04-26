#define GLFW_INCLUDE_NONE

#include "Utils.h"
#include "application/Application.h"
#include "World.h"

int main() {
    Utils::data_dir = "../data/";

    Application application;

    application.init_opengl();

//    Texture2D::Compress("../data/images/dragon.png", "../data/images/dragon.ret");
//
//    return 0;

    auto *World = new AWorld();
    World->BeginPlay();

    application.run();
}