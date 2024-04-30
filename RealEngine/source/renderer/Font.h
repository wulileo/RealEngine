#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "freetype/ftglyph.h"

using std::string;
using std::unordered_map;
using std::vector;

class Texture2D;

class Font {
public:
    static Font *load_from_file(const string &path, unsigned short size);

    static Font *get_font(const string &path);

    void load_character(char c);

    struct Character {
        float left_top_x;
        float left_top_y;
        float right_bottom_x;
        float right_bottom_y;

        Character(float left_top_x, float left_top_y, float right_bottom_x, float right_bottom_y) {
            this->left_top_x = left_top_x;
            this->left_top_y = left_top_y;
            this->right_bottom_x = right_bottom_x;
            this->right_bottom_y = right_bottom_y;
        }
    };

    vector<Character *> load_string(string s);

private:


public:
    Texture2D *font_texture{};
    unsigned short font_size{};
    char *font_file_buffer{};
    FT_Library ft_library{};
    FT_Face ft_face{};
    unsigned short font_texture_size = 1024;

    unsigned short font_texture_fill_x = 0;
    unsigned short font_texture_fill_y = 0;
    unordered_map<char, Character *> character_map;

private:
    static unordered_map<string, Font *> font_map;
};
