#ifndef REALENGINE_SHADER_H
#define REALENGINE_SHADER_H


#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include <glad.h>

using std::string;
using std::unordered_map;

class Shader {

public:
    static Shader *find(const string &name);

private:
    static unordered_map<string, Shader*> shader_map;

public:
    string name;
    unsigned int program_id;

public:
    void parse(const string &name);

    void create_gpu_program(const char *vertex_shader_text, const char *fragment_shader_text);
};


#endif //REALENGINE_SHADER_H
