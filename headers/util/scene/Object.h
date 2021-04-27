#pragma once

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

// Used to hold specific model vertex data
class Object {
public:
    Object(GLfloat* VBOData, int VBOSize, GLuint* IBOData, int IBOSize, GLfloat* colorBufferData, int colorBufferSize);

    GLuint getVAO();

private:
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    GLuint colorBuffer;
};