#include "Shader.h"

using std::string;
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;
using std::pair;

unordered_map<string, Shader*> Shader::shader_map;

void Shader::parse(const std::string &name_in) {
    name = name_in;
    string vertex_path = name + ".vs";
    string fragment_path = name + ".fs";

    ifstream vertex_stream(vertex_path);
    string vertex_shader_source((std::istreambuf_iterator<char>(vertex_stream)), std::istreambuf_iterator<char>());

    ifstream fragment_stream(fragment_path);
    string fragment_shader_source((std::istreambuf_iterator<char>(fragment_stream)), std::istreambuf_iterator<char>());

    create_gpu_program(vertex_shader_source.c_str(), fragment_shader_source.c_str());
}

void Shader::create_gpu_program(const char *vertex_shader_text, const char *fragment_shader_text) {
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader);
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader, sizeof(message), nullptr, message);
        cout << "compile vs error:" << message << endl;
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
    glCompileShader(fragment_shader);
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader, sizeof(message), nullptr, message);
        cout << "compile fs error:" << message << endl;
    }


    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader);
    glAttachShader(program_id, fragment_shader);
    glLinkProgram(program_id);
    GLint link_status = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        GLchar message[256];
        glGetProgramInfoLog(program_id, sizeof(message), nullptr, message);
        std::cout << "link error:" << message << std::endl;
    }
}

Shader *Shader::find(const string &name) {
    auto it = shader_map.find(name);
    if (it != shader_map.end()) {
        return it->second;
    }

    auto *shader = new Shader();
    shader->parse(name);

    shader_map.insert(pair<string, Shader *>(name, shader));

    return shader;
}
