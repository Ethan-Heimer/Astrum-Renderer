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

void Renderer::Shader::Delete(){
    glDeleteProgram(shaderProgramID);
}

unsigned int Renderer::Shader::GetShaderId() const {
    return shaderProgramID;
}
