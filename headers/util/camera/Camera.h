#pragma once

#include <vector>

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
    Camera(CameraController*);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    // !Remove from Camera class eventually!
    void addController(CameraController* controller);
    void setController(int pos);

    // !Remove from Camera class eventually!
    void nextController();

    void update();

private:
    glm::vec3 computeDir();
    glm::vec3 computeRight();

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    // !Remove from Camera class eventually!
    std::vector<CameraController*> controllers;

    CameraController* controller;

    // !Remove from Camera class eventually!
    int controllerPosition;

    glm::vec3 position; 

    float horizontalAngle;
    float verticalAngle;
};
