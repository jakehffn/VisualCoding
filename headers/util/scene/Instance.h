#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"

class Instance {
public:
    Instance(Object object, glm::vec3 pos);
    Instance(Object object, glm::mat4 model);

    void updateModel();
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    void setRotation(glm::vec3 rotation);
    glm::vec3 getRotation();
    void setScale(glm::vec3 scale);
    glm::vec3 getScale();

private:
    Object object;
    glm::mat4 model;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};