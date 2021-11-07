#pragma once

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "ObjLoader.h"
#include "Instance.h"

// Used to hold specific model vertex data
class Object {
public:
    Object(char* OBJPath, GLuint shaderProgramID);

    int addInstance(glm::vec3 position, 
        glm::vec3 scale=glm::vec3(1), glm::vec3 rotation=glm::vec3(0));

    Instance& getInstance(int instanceID);

    GLuint getShaderProgramID();
    GLuint getVAO();
    int getNumVertices();

    int getNumInstances();

    void updateModelMatrices();
    glm::mat4* getModelMatrices();

private:
    GLuint VAO;
    GLuint openGLShaderProgramID;
    GLuint modelsBuffer;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

    std::vector<Instance> instances;
    std::vector<glm::mat4> modelMatrices;
};