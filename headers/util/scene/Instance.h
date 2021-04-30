#pragma once

#include "Object.h"

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Used to have an instance of a specific type of object
class Instance {
public:
    Instance(Object* object, int shaderProgramID, glm::vec3 position, 
        glm::vec3 scale=glm::vec3(1), glm::vec3 rotation=glm::vec3(0));
    Instance(Object* object, GLuint openGLShaderProgramID, glm::mat4 model);

    void updateModel();
    glm::mat4 getModel();

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();

    void setRotation(glm::vec3 rotation);
    glm::vec3 getRotation();

    void setScale(glm::vec3 scale);
    glm::vec3 getScale();

    int getShaderProgramID();
    GLuint getObjectVAO();
    int getObjectNumVertices();
    

private:
    Object* object;
    glm::mat4 model;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    int shaderProgramID;

    bool needsUpdate;
    const bool isStatic;
};