#pragma once

#include "Path.h"

class CirclePath : public Path {
public:
    CirclePath(glm::vec3 circleCenter, float circleRadius, float loft, float pathSpeed);
    void update(glm::vec3& pos, float& horizontalAngle, float& verticalAngle, double time);
private:
    glm::vec3 circleCenter;

    float circleRadius;
    float loft;

    float pathSpeed;
};