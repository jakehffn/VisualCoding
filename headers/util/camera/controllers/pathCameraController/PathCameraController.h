#pragma once

#include "CameraController.h"
#include "Path.h"

#include "Clock.h"

class PathCameraController : public CameraController {
public: 
    PathCameraController(SDL_Window* window, Clock* clock, Path* path);

    void update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right);

private:
    Clock* clock;
    SDL_Window* window;
    Path* path;
};