#include "Font.h"

#include <fstream>

#include "Utils.h"
#include "Texture2D.h"

using std::ifstream;
using std::ios;

unordered_map<string, Font *> Font::font_map;

void Font::load_character(char c) {
    if (character_map[c]) {
        return;
    }

    FT_Load_Glyph(ft_face, FT_Get_Char_Index(ft_face, c), FT_LOAD_DEFAULT);

    FT_Glyph ft_glyph;
    FT_Get_Glyph(ft_face->glyph, &ft_glyph);
    FT_Glyph_To_Bitmap(&ft_glyph, ft_render_mode_normal, 0, 1);

    auto ft_bitmap_glyph = (FT_BitmapGlyph) ft_glyph;
    FT_Bitmap &ft_bitmap = ft_bitmap_glyph->bitmap;

    if (font_texture_fill_x + ft_bitmap.width >= font_texture_size) {
        font_texture_fill_x = 0;
        font_texture_fill_y += font_size;
    }
    if (font_texture_fill_y + font_size >= font_texture_size) {
        return;
    }

    font_texture->UpdateSubImage(font_texture_fill_x, font_texture_fill_y, (int) ft_bitmap.width, (int) ft_bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, ft_bitmap.buffer);

    auto character = new Character((float) font_texture_fill_x / (float) font_texture_size, (float) font_texture_fill_y / (float) font_texture_size, (float) (font_texture_fill_x + ft_bitmap.width) / (float) font_texture_size, (float) (font_texture_fill_y + ft_bitmap.rows) / (float) font_texture_size);
    character_map[c] = character;
    font_texture_fill_x += ft_bitmap.width;
}

Font *Font::load_from_file(const string &path, unsigned short size) {
    Font *font = get_font(path);
    if (font) {
        return font;
    }

    ifstream stream(path, ios::in | ios::binary);
    stream.seekg(0, ios::end);
    long long length = stream.tellg();
    stream.seekg(0, ios::beg);
    char *buffer = new char[length];
    stream.read(buffer, length);

    FT_Library ft_library = nullptr;
    FT_Face ft_face = nullptr;
    FT_Init_FreeType(&ft_library);
    FT_Error error = FT_New_Memory_Face(ft_library, (const FT_Byte *) buffer, (long) length, 0, &ft_face);
    if (error != 0) {
        return nullptr;
    }

    FT_Select_Charmap(ft_face, FT_ENCODING_UNICODE);

    auto ft_size = (FT_F26Dot6) (size * (1 << 6));

    FT_Set_Char_Size(ft_face, ft_size, 0, 72, 72);

    if (!ft_face) {
        return nullptr;
    }

    font = new Font();
    font->font_size = size;
    font->font_file_buffer = buffer;
    font->ft_library = ft_library;
    font->ft_face = ft_face;
    font_map[path] = font;

    auto *pixels = (unsigned char *) malloc(font->font_texture_size * font->font_texture_size);
    memset(pixels, 0, font->font_texture_size * font->font_texture_size);
    font->font_texture = Texture2D::Create(font->font_texture_size, font->font_texture_size, GL_RED, GL_RED, GL_UNSIGNED_BYTE, pixels);
    delete pixels;

    return font;
}

Font *Font::get_font(const string &path) {
    return font_map[path];
}

vector<Font::Character *> Font::load_string(string s) {
    vector<Character *> result;

    for (auto c: s) {
        load_character(c);
        auto character = character_map[c];
        if (character) {
            result.push_back(character);
        }
    }

    return result;
}
