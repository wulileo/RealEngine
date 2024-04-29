#include "Texture2D.h"
#include "stb_image.h"

Texture2D *Texture2D::Load(const std::string &path) {
    std::ifstream stream(path, std::ios::in | std::ios::binary);
    REImageHead head{};
    stream.read((char *) &head, sizeof(REImageHead));

    bool isRET = head.type[0] == 'r' && head.type[1] == 'e' && head.type[2] == 't';
    return isRET ? LoadWithCompress(path) : LoadWithoutCompress(path);
}

Texture2D *Texture2D::LoadWithoutCompress(const std::string &path) {
    auto *texture2d = new Texture2D();
    stbi_set_flip_vertically_on_load(true);
    int channel;
    unsigned char *data = stbi_load(path.c_str(), &(texture2d->width), &(texture2d->height), &channel, 0);
    if (data != nullptr) {
        switch (channel) {
            case 1: {
                texture2d->format = GL_ALPHA;
                break;
            }
            case 3: {
                texture2d->format = GL_RGB;
                break;
            }
            case 4: {
                texture2d->format = GL_RGBA;
                break;
            }
            default: {
                break;
            }
        }
    }

    glGenTextures(1, &texture2d->id);
    glBindTexture(GL_TEXTURE_2D, texture2d->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2d->width, texture2d->height, 0, texture2d->format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture2d;
}

void Texture2D::Compress(const std::string &source_path, const std::string &target_path) {
    stbi_set_flip_vertically_on_load(true);

    int level = 0;
    int width;
    int height;
    int channel;

    unsigned char *data = stbi_load(source_path.c_str(), &width, &height, &channel, STBI_rgb_alpha);

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
                compress_format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
                break;
            }
            case 4: {
                source_format = GL_RGBA;
                compress_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
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

Texture2D *Texture2D::Create(int width, int height, unsigned int server_format, unsigned int client_format, unsigned int data_type, unsigned char *data) {
    auto *texture2d = new Texture2D();
    texture2d->format = server_format;
    texture2d->width = width;
    texture2d->height = height;

    //1. 通知显卡创建纹理对象，返回句柄;
    glGenTextures(1, &(texture2d->id));

    glBindTexture(GL_TEXTURE_2D, texture2d->id);

    glTexImage2D(GL_TEXTURE_2D, 0, (int) texture2d->format, texture2d->width, texture2d->height, 0, client_format, data_type, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return texture2d;
}

Texture2D *Texture2D::LoadWithCompress(const std::string &path) {
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

    glCompressedTexImage2D(GL_TEXTURE_2D, head.level, texture2D->format, texture2D->width, texture2D->height, 0, head.size, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    delete (data);

    return texture2D;
}

void Texture2D::UpdateSubImage(int x, int y, int w, int h, unsigned int client_format, unsigned int data_type, unsigned char *data) const {
    if (w <= 0 || h <= 0) {
        return;
    }
    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, client_format, data_type, data);
}
