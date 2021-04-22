#pragma once

#include <GL/glu.h>
#include <SDL.h>

#include "Camera.h"
#include "UserCameraController.h"
#include "Clock.h"

class VisualProgram {
public:
    virtual bool init(SDL_Window* window) = 0;
    virtual void run() = 0;
};

class OpenGLTutorial : public VisualProgram {
public:
    ~OpenGLTutorial();
    bool init(SDL_Window* window);
    void run();
    
private:
    GLuint gProgramID = 0;
    SDL_Window* window = NULL;

    Clock* clock;
    Input* input;
    Camera* camera;
    CameraController* controller;
};