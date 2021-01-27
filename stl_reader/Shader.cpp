#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string& filepath):
    FilePath_(filepath),
    RendererID_(0) 
{
    CompileShader(RendererID_, filepath);
    ShaderProgramSource source = ParseShader(filepath);
    RendererID_ = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader(){
    GLCall(glDeleteProgram(RendererID_));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type); // create shader object of given type
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr); // macro for replacing source code in shader object
    // id : handle, count : number of entries in string and string length array
    // string : array of pointers to strings (double ptr)
    // pointer to array of length of strings in string array

    glCompileShader(id); // compiles source code strings stored inside 
    // error handling: glGetShaderiv(id_of_shader_obj, *object parameter* GL_COMPILE_STATUS, 
    // *returns the object inside* params)

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); // alloca allocates dynamically on the stack

        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << '\n';
        std::cout << message << std::endl;
    }

    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream fin(filepath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;
    while (getline(fin, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    // create program
    unsigned int program = glCreateProgram();
    unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

void Shader::Bind() const {
    GLCall(glUseProgram(RendererID_));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    int loc;
    loc = GetUniformLocation(name);
    GLCall(glUniform4f(loc, v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name) {
    if (UniformLocationCache_.find(name) != UniformLocationCache_.end())
        return UniformLocationCache_[name];

    int location;

    GLCall(location = glGetUniformLocation(RendererID_, name.c_str()));

    if (location == -1)
        std::cout << "Warning! uniform " << name << " doesn't exist!" << std::endl;
    else
        UniformLocationCache_[name] = location;
    
    return location;
}