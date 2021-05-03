#include "BasicShader.h"

BasicShader::BasicShader() {
    
    std::string vertexShaderPath = "./src/shaderPrograms/BasicShader/vertexShader.glsl";
    std::string fragmentShaderPath = "./src/shaderPrograms/BasicShader/fragmentShader.glsl";

    this->openGLShaderProgramID = LoadShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    this->MVPuniformID = glGetUniformLocation(this->openGLShaderProgramID, "MVP");
    this->MuniformID = glGetUniformLocation(this->openGLShaderProgramID, "M");
    this->VuniformID = glGetUniformLocation(this->openGLShaderProgramID, "V");
    this->LightID = glGetUniformLocation(this->openGLShaderProgramID, "LightPosition_worldspace");
}

GLuint BasicShader::getOpenGLShaderProgramID() {
    return this->openGLShaderProgramID;
}

void BasicShader::renderSetup(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    
    glm::mat4 MVP = projection*view*model;

    glm::vec3 lightPos = glm::vec3(50,100,35);
    glUniform3f(this->LightID, lightPos.x, lightPos.y, lightPos.z);

    glUniformMatrix4fv(this->MVPuniformID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(this->MuniformID, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(this->VuniformID, 1, GL_FALSE, &view[0][0]);

}