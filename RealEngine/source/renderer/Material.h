#ifndef REALENGINE_MATERIAL_H
#define REALENGINE_MATERIAL_H

#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

#include "Shader.h"
#include "Texture2D.h"
#include "Utils.h"

using std::string;
using std::vector;
using std::pair;

class Shader;

class Texture2D;

class Material {
public:
    static Material *parse(const string &path);

    void set_texture(const string &name, Texture2D *texture2D);

public:
    Shader *shader;

    vector<pair<string, Texture2D *>> textures;

    vector<pair<string, float *>> uniform_matrix4fv_vec;

    vector<pair<string, int>> uniform_1i_vec;
};


#endif //REALENGINE_MATERIAL_H
