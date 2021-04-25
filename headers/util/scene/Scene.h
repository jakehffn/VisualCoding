#pragma once

#include <vector>

#include "Object.h"
#include "Instance.h"

class Scene {
public:
    Scene(GLuint uniformID);

    void addInstance(Instance* instance);
    void render(glm::mat4 projection, glm::mat4 view);

    int getNumInstances();
    
private:
    GLuint uniformID;
    std::vector<Instance*> instances;
    int numInstances;
};