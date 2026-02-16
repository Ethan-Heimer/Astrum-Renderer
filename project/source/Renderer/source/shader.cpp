#include "shader.h"

#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <sstream>

Renderer::Shader::Shader(std::string vertexPath, std::string fragmentPath){
    // 2. Load and compile shaders
    //shaders
    //shader files
    std::ifstream vertexFile, fragmentFile{};
    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    
    std::stringstream vertexStream;
    std::stringstream fragmentStream;

    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();

    std::string vertexString = vertexStream.str();
    std::string fragmentString = fragmentStream.str();
 
    const char* vertexSource = vertexString.c_str();
    const char* fragmentSource = fragmentString.c_str();
    
    //shader compilation
    //vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }

    //fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }

    //linking shaders
    shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING::COMPILAITON FAILED\n" << 
        infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Renderer::Shader::~Shader(){
    Delete();
}

void Renderer::Shader::Use(){
    glUseProgram(shaderProgramID);

    /* Set Texture Units */
}

void Renderer::Shader::Delete(){
    glDeleteProgram(shaderProgramID);
}

void Renderer::Shader::SetBool(const std::string& name, bool value){
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

void Renderer::Shader::SetInt(const std::string& name, int value){
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

void Renderer::Shader::SetUnsignedInt(const std::string& name, unsigned int value){
    glUniform1ui(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

void Renderer::Shader::SetFloat(const std::string& name, float value){
    glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

void Renderer::Shader::SetVector2(const std::string& name, float x, float y){
    glUniform2f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y);
}

void Renderer::Shader::SetVector3(const std::string& name, float x, float y, float z){
    glUniform3f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z);
}

void Renderer::Shader::SetVector4(const std::string& name, float x, float y, float z, float w){
    glUniform4f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z, w);
}

void Renderer::Shader::SetMatrix4x4(const std::string& name, const float* matrix){
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, matrix);
}

unsigned int Renderer::Shader::GetId() const {
    return shaderProgramID;
}
