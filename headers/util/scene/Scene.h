#pragma once

#include <vector>

#include "Object.h"
#include "Instance.h"

class Scene {
public:
    Scene(GLint programID);

    void addInstance(Instance* instance);
    void render(glm::mat4 projection, glm::mat4 view);

    int getNumInstances();

    void setUniformIDs();
    
private:
    GLint programID;

    GLint MVPuniformID;
    GLint MuniformID;
    GLint VuniformID;
    GLuint LightID;

    std::vector<Instance*> instances;
};