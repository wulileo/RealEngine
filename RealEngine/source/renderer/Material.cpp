#include "Material.h"

Material *Material::parse(const string &path) {
    rapidxml::file<> xml(path.c_str());
    rapidxml::xml_document<> document;
    document.parse<0>(xml.data());

    rapidxml::xml_node<> *material_node = document.first_node("material");
    if (material_node == nullptr) {
        return nullptr;
    }

    rapidxml::xml_attribute<> *material_shader_attribute = material_node->first_attribute("shader");
    if (material_shader_attribute == nullptr) {
        return nullptr;
    }

    auto *material = new Material();

    const string shader_path = Utils::data_dir + material_shader_attribute->value();
    material->shader = Shader::find(shader_path);

    rapidxml::xml_node<> *material_texture_node = material_node->first_node("texture");
    while (material_texture_node != nullptr) {
        rapidxml::xml_attribute<> *texture_name_attribute = material_texture_node->first_attribute("name");
        if (texture_name_attribute == nullptr) {
            return nullptr;
        }

        rapidxml::xml_attribute<> *texture_image_attribute = material_texture_node->first_attribute("image");
        if (texture_image_attribute == nullptr) {
            return material;
        }

        string shader_property_name = texture_name_attribute->value();
        const string image_path = Utils::data_dir + texture_image_attribute->value();
        material->textures.emplace_back(texture_name_attribute->value(), Texture2D::Load(image_path));

        material_texture_node = material_texture_node->next_sibling("texture");
    }
    return material;
}

void Material::set_texture(const string &name, Texture2D *texture2D) {
    for (auto &pair: textures) {
        if (pair.first == name) {
            delete (pair.second);
            pair.second = texture2D;
            break;
        }
    }
}
