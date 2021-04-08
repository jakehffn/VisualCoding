#pragma once

#include <string>
#include <gl/glew.h>

class ShaderLoader {
public:
    ShaderLoader(GLuint gProgramID, GLuint vertexShader, GLuint fragmentShader);
    bool loadShaders(std::string vertexPath, std::string fragmentPath);
private:
    char* getShaderSource(std::string shaderPath);
    GLint compileShader(GLuint shader, const GLchar* shaderSource);
    void printLog(GLuint glComp);

    GLuint programID_;
    GLuint vertexShader_;
    GLuint fragmentShader_;
};