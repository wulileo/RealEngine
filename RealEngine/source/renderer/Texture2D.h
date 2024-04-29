#ifndef REALENGINE_TEXTURE2D_H
#define REALENGINE_TEXTURE2D_H

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>

#include "glad.h"
#include "glext.h"

class Texture2D {
private:
    Texture2D() {};

public:
    static Texture2D *Load(const std::string &path);

    static Texture2D *LoadWithCompress(const std::string &path);

    static Texture2D *LoadWithoutCompress(const std::string &path);

    static Texture2D *Create(int width, int height, unsigned int server_format, unsigned int client_format, unsigned int data_type, unsigned char *data);

    static void Compress(const std::string &source_path, const std::string &target_path);

    void UpdateSubImage(int x,int y,int width,int height,unsigned int client_format,unsigned int data_type,unsigned char* data) const;

    ~Texture2D() = default;

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
