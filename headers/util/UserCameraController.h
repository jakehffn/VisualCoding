#pragma once

#include "CameraController.h"

#include <SDL.h>

#include "Clock.h"
#include "Input.h"
#include "consts.h"

class UserCameraController : public CameraController {
public:
    UserCameraController(SDL_Window* window, Clock* clock, Input* input);

    void update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right);

private:
    Clock* clock;
    SDL_Window* window;
    Input* input;

    float horizontalAngle;
    float verticalAngle;
};