#pragma once

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "ObjLoader.h"

// Used to hold specific model vertex data
class Object {
public:
    Object(char* OBJPath);

    GLuint getVAO();
    int getNumVertices();

private:
    GLuint VAO;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};