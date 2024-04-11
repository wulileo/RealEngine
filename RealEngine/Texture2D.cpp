//
// Created by Administrator on 2024/4/11.
//

#include <fstream>
#include "Texture2D.h"
#include "stb/stb_image.h"

Texture2D *Texture2D::Load(std::string &path) {
    Texture2D *texture2D;
    texture2D = new Texture2D();

    std::ifstream stream(path, std::ios::in | std::ios::binary);
    REImageHead head{};
    stream.read((char *) &head, sizeof(REImageHead));

    if (head.type[0] != 'r' || head.type[1] != 'e' || head.type[2] != 't') {
        std::cout << "Load Texture File Error : " << path << std::endl;
        return texture2D;
    }

    unsigned char *data;
    data = (unsigned char *) malloc(head.size);
    stream.read((char *) data, head.size);
    stream.close();

    texture2D->format = head.format;
    texture2D->width = head.weight;
    texture2D->height = head.height;

    glGenTextures(1, &(texture2D->id));

    glBindTexture(GL_TEXTURE_2D, texture2D->id);

    glCompressedTexImage2D(GL_TEXTURE_2D, head.level, texture2D->format, texture2D->width,
                           texture2D->height, 0,
                           head.size, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    delete (data);

    return texture2D;
}

void Texture2D::Compress(const std::string &source_path, const std::string &target_path) {
    stbi_set_flip_vertically_on_load(true);

    int level = 0;
    int width;
    int height;
    int channel;

    unsigned char *data = stbi_load(source_path.c_str(), &width, &height, &channel, 0);

    int source_format = GL_RGB;
    int compress_format = GL_COMPRESSED_RGB;
    if (data) {
        switch (channel) {
            case 1: {
                source_format = GL_ALPHA;
                break;
            }
            case 3: {
                source_format = GL_RGB;
                compress_format = GL_COMPRESSED_RGB;
                break;
            }
            case 4: {
                source_format = GL_RGBA;
                compress_format = GL_COMPRESSED_RGBA;
                break;
            }
            default:
                break;
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, compress_format, width, height, 0, source_format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    GLint success = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &success);
    GLint size = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &size);
    GLint format = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);

    void *img = malloc(size);
    glGetCompressedTexImage(GL_TEXTURE_2D, 0, img);

    std::ofstream stream(target_path, std::ios::out | std::ios::binary);

    REImageHead head{};
    head.type[0] = 'r';
    head.type[1] = 'e';
    head.type[2] = 't';
    head.level = level;
    head.weight = width;
    head.height = height;
    head.format = format;
    head.size = size;

    stream.write((char *) &head, sizeof(REImageHead));
    stream.write((char *) img, size);
    stream.close();
}
