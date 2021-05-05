#pragma once

#include "ShaderProgram.h"
#include <string>

// This shader will have the color of objects be dependent on their yPos
class TopographicShader : public ShaderProgram {
public:
    TopographicShader(float yLow, float yHigh, glm::vec3 lowColor, glm::vec3 highColor);

    GLuint getOpenGLShaderProgramID();
    void renderSetup(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

private:
    GLuint openGLShaderProgramID;

    GLint MVPuniformID;
    GLint MuniformID;
    GLint VuniformID;

    GLuint LightID;
    GLuint yLowID;
    GLuint yHighID;
    GLuint lowColorID;
    GLuint highColorID;

    float yLow;
    float yHigh;
    glm::vec3 lowColor;
    glm::vec3 highColor;
};