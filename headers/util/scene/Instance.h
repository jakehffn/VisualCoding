#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Used to have an instance of a specific type of object
class Instance {
public:
    Instance(glm::vec3 position, 
        glm::vec3 scale=glm::vec3(1), glm::vec3 rotation=glm::vec3(0));
    Instance(glm::mat4 model);

    glm::mat4 getModel();
    bool needsUpdate() const;

    void setPosition(glm::vec3 position);
    void addPosition(glm::vec3 position);
    glm::vec3 getPosition();

    void setRotation(glm::vec3 rotation);
    glm::vec3 getRotation();

    void setScale(glm::vec3 scale);
    glm::vec3 getScale();
    

private:

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    bool changed;
    const bool isStatic;
};