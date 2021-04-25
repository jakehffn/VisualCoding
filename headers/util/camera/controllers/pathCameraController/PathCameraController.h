#pragma once

#include "CameraController.h"
#include "Path.h"

#include "Clock.h"

class PathCameraController : public CameraController {
public: 
    PathCameraController(Clock* clock, Path* path);

    void update(glm::vec3& pos, float& horizontalAngle, float& verticalAngle);

private:
    Clock* clock;
    Path* path;
};