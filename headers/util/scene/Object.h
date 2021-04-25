#pragma once

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

// Used to hold specific model vertex data
class Object {
public:
    Object(GLfloat* vboData, GLfloat* colorBufferData, int size);

    GLuint getVBO();
    GLuint getColorBuffer();

private:
    GLuint vbo;
    GLuint colorBuffer;
};