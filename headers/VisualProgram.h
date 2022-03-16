#pragma once

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Scene.h"
#include "UserCameraController.h"
#include "Clock.h"

class VisualProgram {
protected:
    GLuint programID = 0;
    SDL_Window* window = NULL;

    Clock* clock;
    Input* input;
    Scene* scene;

    CameraController* cameraController;

public:
    VisualProgram(SDL_Window* window, bool render);
    virtual void init() = 0;
    virtual void run() = 0;
};