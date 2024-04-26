#ifndef REALENGINE_APPLICATION_H
#define REALENGINE_APPLICATION_H

#include <string>
#include <glad.h>
#include <glfw3.h>

#include "Screen.h"

using std::string;

class Application {
public:
    void init_opengl();

    void run() const;

    void tick() const;

    void update_screen() const;

    static void render();

private:


public:
    string data_path;

    GLFWwindow *window;

private:

};

#endif //REALENGINE_APPLICATION_H
