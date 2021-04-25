#pragma once

#include "CameraController.h"

#include <SDL.h>

#include "Clock.h"
#include "Input.h"
#include "consts.h"

class UserCameraController : public CameraController {
public:
    UserCameraController(SDL_Window* window, Clock* clock, Input* input);

    void update(glm::vec3& pos, float& horizontalAngle, float& verticalAngle);

private:
    void updateAngles(float& horizontalAngle, float& verticalAngle);

    glm::vec3 computeForward(float horizontalAngle, float verticalAngle);

    Clock* clock;
    SDL_Window* window;
    Input* input;
};