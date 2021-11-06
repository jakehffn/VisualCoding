#include "InstancedShader.h"

InstancedShader::InstancedShader(float yLow, float yHigh, glm::vec3 lowColor, glm::vec3 highColor) :
    yLow{ yLow }, yHigh{ yHigh }, lowColor{ lowColor }, highColor{ highColor } {
    
    std::string vertexShaderPath = "./src/shaderPrograms/TopographicShader/vertexShader.glsl";
    std::string fragmentShaderPath = "./src/shaderPrograms/TopographicShader/fragmentShader.glsl";

    this->openGLShaderProgramID = LoadShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    this->PuniformID = glGetUniformLocation(this->openGLShaderProgramID, "P");
    this->VuniformID = glGetUniformLocation(this->openGLShaderProgramID, "V");
    this->LightID = glGetUniformLocation(this->openGLShaderProgramID, "LightPosition_worldspace");

    this->yLowID = glGetUniformLocation(this->openGLShaderProgramID, "yLow");
    this->yHighID = glGetUniformLocation(this->openGLShaderProgramID, "yHigh");
    this->lowColorID = glGetUniformLocation(this->openGLShaderProgramID, "lowColor");
    this->highColorID = glGetUniformLocation(this->openGLShaderProgramID, "highColor");
}

GLuint InstancedShader::getOpenGLShaderProgramID() {
    return this->openGLShaderProgramID;
}

void InstancedShader::renderSetup(glm::mat4 view, glm::mat4 projection) {
    
    glm::vec3 lightPos = glm::vec3(50,100,35);
    glUniform3f(this->LightID, lightPos.x, lightPos.y, lightPos.z);

    glUniformMatrix4fv(this->PuniformID, 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(this->VuniformID, 1, GL_FALSE, &view[0][0]);

    glUniform1f(this->yLowID, yLow);
    glUniform1f(this->yHighID, yHigh);
    glUniform3f(this->lowColorID, this->lowColor.x, this->lowColor.y, this->lowColor.z);
    glUniform3f(this->highColorID, this->highColor.x, this->highColor.y, this->highColor.z);
}