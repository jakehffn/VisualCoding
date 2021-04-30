#pragma once

#include "VisualProgram.h"

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderLoader.h"
#include "consts.h"

#include "Camera.h"
#include "UserCameraController.h"
#include "Clock.h"
#include "CirclePath.h"

#include "UserCameraController.h"
#include "PathCameraController.h"

class OpenGLTutorial : public VisualProgram {
public:
    ~OpenGLTutorial();
    void init(SDL_Window* window);
    void run();
    
private:
    GLuint programID = 0;
    SDL_Window* window = NULL;

    Clock* clock;
    Input* input;
    Camera* camera;
    CameraController* controller;
};