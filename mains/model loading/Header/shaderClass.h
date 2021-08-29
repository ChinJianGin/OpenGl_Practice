#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

//#define USING_STRING

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#ifdef USING_STRING
std::string get_file_contents(const std::string filename);
#else
std::string get_file_contents(const char* filename);
#endif

class Shader
{
public:
    GLuint ID;
#ifdef USING_STRING
    Shader(const std::string vertexFile, const std::string fragmentFile);
#else
    Shader(const char* vertexFile, const char* fragmentFile);
#endif

    void Activate();
    void Delete();

private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif