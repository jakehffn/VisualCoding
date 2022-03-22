#pragma once

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "ObjLoader.h"

// Used to hold specific model vertex data
class Object {
public:
    Object();
    Object(char* OBJPath);
    Object(std::vector<glm::vec3> vertices);

    GLuint getVAO();
    int getNumVertices();
    void updateVertices(std::vector<glm::vec3> vertices);


private:
    GLuint VAO;
    GLuint verticesBuffer;
    GLuint uvsBuffer;
    GLuint normalsBuffer;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

    void bufferData();
};