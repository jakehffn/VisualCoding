#pragma once

// GLEW must come before OpenGL
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

class VisualProgram {
public:
    virtual void init(SDL_Window* window) = 0;
    virtual void run() = 0;
};

