#pragma once

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "consts.h"
#include "CameraController.h"

/*
    The Camera class handles generation of the view and projection matricies 
using the position, direction, and the vector pointing to the right which are 
all generated in an instance of a implementation of the CameraController class.

No time delta should be tracked within the Camera class.
*/

class Camera {
public:
    Camera(SDL_Window*, CameraController*);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void update();

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    SDL_Window* window;
    CameraController* controller;

    glm::vec3 position; 
    glm::vec3 direction;
    glm::vec3 right; // Vec that points to the right of the camera
};
