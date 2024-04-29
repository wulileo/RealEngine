#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "freetype/ftglyph.h"

using std::string;
using std::unordered_map;

class Texture2D;

class Font {
public:
    void load_character(char c) const;

    static Font *load_from_file(const string &path, unsigned short size);

    static Font *get_font(const string &path);

private:


public:
    Texture2D *font_texture;
    unsigned short font_size;
    char *font_file_buffer;
    FT_Library ft_library;
    FT_Face ft_face;
    unsigned short font_texture_size = 1024;

private:
    static unordered_map<string, Font *> font_map;
};
