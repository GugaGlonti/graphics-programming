#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "shaderClass.h"

std::string getFileContents(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::string error_msg = "ERROR: Could not open shader file: ";
        error_msg += filename;
        std::cerr << error_msg << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    std::string source = buffer.str();
    if (source.empty()) {
        std::string error_msg = "WARNING: Shader file is empty: ";
        error_msg += filename;
        std::cerr << error_msg << std::endl;
    }
    
    return source;
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    std::string vertexShaderSource = getFileContents(vertexPath);
    std::string fragmentShaderSource = getFileContents(fragmentPath);
    const GLchar* vertexShaderCode = vertexShaderSource.c_str();
    const GLchar* fragmentShaderCode = fragmentShaderSource.c_str();
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(this->ID);
}

void Shader::Delete() {
    glDeleteProgram(this->ID);
}
