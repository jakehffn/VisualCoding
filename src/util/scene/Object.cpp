#include "Object.h"

Object::Object(GLfloat* VBOData, int VBOSize, GLuint* IBOData, int IBOSize, GLfloat* colorBufferData, int colorBufferSize) {

    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
    glGenBuffers(1, &(this->IBO));

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, VBOSize, VBOData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBOSize, IBOData, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        3*sizeof(GLfloat),    // stride
        (void*)0            // array buffer offset
    );

    glGenBuffers(1, &(this->colorBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colorBufferSize, colorBufferData, GL_STATIC_DRAW);
    
    glVertexAttribPointer(
        1,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

GLuint Object::getVAO() {
    return this->VAO;
}