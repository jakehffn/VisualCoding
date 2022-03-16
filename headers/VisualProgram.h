#pragma once

#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "consts.h"

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

    bool renderParam;

    FILE* ffmpeg;
    int* frameBuffer;

public:
    VisualProgram(SDL_Window* window, bool render);
    ~VisualProgram();
    virtual void init() = 0;
    virtual void run() = 0;
};