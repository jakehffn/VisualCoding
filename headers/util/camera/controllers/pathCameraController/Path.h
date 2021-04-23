#pragma once

#include <glm/glm.hpp>

class Path {
public:
    virtual void update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right, double time) = 0;
};