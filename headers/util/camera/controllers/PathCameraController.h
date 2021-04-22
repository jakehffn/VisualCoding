#pragma once

#include "CameraController.h"

#include "Clock.h"

class PathCameraController : public CameraController {
public: 
    PathCameraController(SDL_Window* window, Clock* clock);

    void update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right);

private:
    Clock* clock;
    SDL_Window* window;

    float horizontalAngle;
    float verticalAngle;

    double timePassed;
};