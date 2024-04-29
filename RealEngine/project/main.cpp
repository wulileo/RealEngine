#define GLFW_INCLUDE_NONE

#include <iostream>
#include <filesystem>

#include "Utils.h"
#include "application/Application.h"
#include "World.h"


int main() {
    std::filesystem::path current_path = std::filesystem::current_path();

    std::cout << "working directory:" << current_path << std::endl;

    Utils::data_dir = "../data/";

    Application application;

    application.init_opengl();

//    Texture2D::Compress("../data/images/dragon.png", "../data/images/dragon.ret");
//
//    return 0;

    auto *World = new AWorld("World");
    World->BeginPlay();

    application.run();
}