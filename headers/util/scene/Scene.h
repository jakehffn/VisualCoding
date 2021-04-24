#pragma once

#include "Object.h"
#include "Instance.h"

class Scene {
public:
    ~Scene();

    void addInstance(Instance instance);
    void render();
    
private:
    Instance* instances;
};