#include "Object.h"

Object::Object(GLfloat* vboData, GLfloat* colorBufferData, int size) {

    glGenBuffers(1, &(this->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vboData, GL_STATIC_DRAW);

    glGenBuffers(1, &(this->colorBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, colorBufferData, GL_STATIC_DRAW);
}

GLuint Object::getVBO() {
    return this->vbo;
}

GLuint Object::getColorBuffer() {
    return this->colorBuffer;
}