#include "Object.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Object::Object(char* OBJPath, GLuint shaderProgramID) : openGLShaderProgramID{ shaderProgramID },
    instances{ std::vector<Instance>() }, modelMatrices{ std::vector<glm::mat4>() } {

        bool res = loadOBJ(OBJPath, this->vertices, this->uvs, this->normals);
        
        glGenVertexArrays(1, &(this->VAO));

        glBindVertexArray(this->VAO);

        GLuint verticesBuffer;
        glGenBuffers(1, &verticesBuffer);
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

        GLuint uvsBuffer;
        glGenBuffers(1, &uvsBuffer);
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

        GLuint normalsBuffer;
        glGenBuffers(1, &normalsBuffer);
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

        glGenBuffers(1, &this->modelsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->modelsBuffer);
    
        // vertex attributes
        glEnableVertexAttribArray(3); 
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
        glEnableVertexAttribArray(4); 
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(1 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(5); 
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6); 
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
}

int Object::addInstance(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {

    this->instances.emplace_back(position, scale, rotation);

    // glBindVertexArray(this->VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, this->modelsBuffer);
    // glBufferData(GL_ARRAY_BUFFER, 2500 * sizeof(glm::mat4), &this->modelMatrices.data()[0], GL_STATIC_DRAW);

    // // vertex attributes
    // std::size_t vec4Size = sizeof(glm::vec4);
    // glEnableVertexAttribArray(3); 
    // glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    // glEnableVertexAttribArray(4); 
    // glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    // glEnableVertexAttribArray(5); 
    // glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    // glEnableVertexAttribArray(6); 
    // glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    // glVertexAttribDivisor(3, 1);
    // glVertexAttribDivisor(4, 1);
    // glVertexAttribDivisor(5, 1);
    // glVertexAttribDivisor(6, 1);

    // printf("%d\n", this->modelMatrices.size());
    
    // glBindVertexArray(0);

    return this->instances.size() - 1;

}

Instance& Object::getInstance(int instanceID) {

    assert(instanceID < instances.size());
    return this->instances[instanceID];
}

GLuint Object::getShaderProgramID() {
    return this->openGLShaderProgramID;
}

GLuint Object::getVAO() {
    return this->VAO;
}

int Object::getNumVertices() {
    return this->vertices.size();
}

int Object::getNumInstances() {
    return this->instances.size();
}

void Object::updateModelMatrices() {
    
    this->modelMatrices.clear();

    for (auto& instance : instances) {

        this->modelMatrices.push_back(instance.getModel());
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->modelsBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->instances.size() * sizeof(glm::mat4), this->modelMatrices.data(), GL_STATIC_DRAW);

}

glm::mat4* Object::getModelMatrices() {
    return modelMatrices.data();
}
