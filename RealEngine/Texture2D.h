#ifndef REALENGINE_TEXTURE2D_H
#define REALENGINE_TEXTURE2D_H

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>

class Texture2D {
private:
    Texture2D() {};

    ~Texture2D() = default;

public:
    static Texture2D *Load(std::string &path);

    static void Compress(const std::string &source_path, const std::string &target_path);

public:
    int level{};
    int width{};
    int height{};

    GLenum format{};
    GLuint id{};
};

struct REImageHead {
    char type[3];
    int level;
    int weight;
    int height;
    int format;
    int size;
};

#endif //REALENGINE_TEXTURE2D_H
