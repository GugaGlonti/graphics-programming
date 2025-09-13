#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <string>

std::string getFileContents(const GLchar* filePath);

class Shader
{
    public:
        GLuint ID;
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        void Activate();
        void Delete();
};

#endif
