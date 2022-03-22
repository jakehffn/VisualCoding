#include "Object.h"

Object::Object() {

    glGenVertexArrays(1, &(this->VAO));

    glGenBuffers(1, &(this->verticesBuffer));
    glGenBuffers(1, &(this->uvsBuffer));
    glGenBuffers(1, &(this->normalsBuffer));
}

Object::Object(char* OBJPath) : Object::Object() {

	bool res = loadOBJ(OBJPath, this->vertices, this->uvs, this->normals);
    
    this->bufferData();
}

Object::Object(std::vector<glm::vec3> vertices) : Object::Object() {

    this->updateVertices(vertices);

    this->bufferData();
}

void Object::updateVertices(std::vector<glm::vec3> vertices) {

    this->vertices = vertices;

    // TODO: Generate normals
    // TODO: Generate uvs

}

GLuint Object::getVAO() {
    return this->VAO;
}

int Object::getNumVertices() {
    return this->vertices.size();
}

void Object::bufferData() {

    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,    // stride
        (void*)0            // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->uvs.size()*sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

    glVertexAttribPointer(
        1,                                // attribute
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size()*sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(
        2,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}