#include "TopographicShader.h"

TopographicShader::TopographicShader(float yLow, float yHigh, glm::vec3 lowColor, glm::vec3 highColor) :
    yLow{ yLow }, yHigh{ yHigh }, lowColor{ lowColor }, highColor{ highColor } {
    
    std::string vertexShaderPath = "./src/shaderPrograms/TopographicShader/vertexShader.glsl";
    std::string fragmentShaderPath = "./src/shaderPrograms/TopographicShader/fragmentShader.glsl";

    this->openGLShaderProgramID = LoadShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    this->MVPuniformID = glGetUniformLocation(this->openGLShaderProgramID, "MVP");
    this->MuniformID = glGetUniformLocation(this->openGLShaderProgramID, "M");
    this->VuniformID = glGetUniformLocation(this->openGLShaderProgramID, "V");
    this->LightID = glGetUniformLocation(this->openGLShaderProgramID, "LightPosition_worldspace");

    this->yLowID = glGetUniformLocation(this->openGLShaderProgramID, "yLow");
    this->yHighID = glGetUniformLocation(this->openGLShaderProgramID, "yHigh");
    this->lowColorID = glGetUniformLocation(this->openGLShaderProgramID, "lowColor");
    this->highColorID = glGetUniformLocation(this->openGLShaderProgramID, "highColor");
}

GLuint TopographicShader::getOpenGLShaderProgramID() {
    return this->openGLShaderProgramID;
}

void TopographicShader::renderSetup(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    
    glm::mat4 MVP = projection*view*model;

    glm::vec3 lightPos = glm::vec3(50,100,35);
    glUniform3f(this->LightID, lightPos.x, lightPos.y, lightPos.z);

    glUniformMatrix4fv(this->MVPuniformID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(this->MuniformID, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(this->VuniformID, 1, GL_FALSE, &view[0][0]);

    glUniform1f(this->yLowID, yLow);
    glUniform1f(this->yHighID, yHigh);
    glUniform3f(this->lowColorID, this->lowColor.x, this->lowColor.y, this->lowColor.z);
    glUniform3f(this->highColorID, this->highColor.x, this->highColor.y, this->highColor.z);
}