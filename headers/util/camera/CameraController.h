#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Clock.h"


class CameraController {
public:
    virtual void update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right) = 0;
};

