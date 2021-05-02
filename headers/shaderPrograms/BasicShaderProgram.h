#pragma once

#include "ShaderProgram.h"
#include <string>

class BasicShaderProgram : public ShaderProgram {
public:
    BasicShaderProgram();

    GLuint getOpenGLShaderProgramID();
    void renderSetup(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

private:
    GLuint openGLShaderProgramID;

    GLint MVPuniformID;
    GLint MuniformID;
    GLint VuniformID;
    GLuint LightID;
};