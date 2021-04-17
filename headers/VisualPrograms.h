#pragma once

#include <GL/glu.h>
#include <SDL.h>

#include "Controls.hpp"

class VisualProgram {
public:
    virtual bool init(SDL_Window* gWindow) = 0;
    virtual void run() = 0;
};

class OpenGLTutorial : public VisualProgram {
public:
    ~OpenGLTutorial();
    bool init(SDL_Window* gWindow);
    void run();
    void eventHandler(SDL_Event e);
    
private:
    GLuint gProgramID = 0;
    SDL_Window* gWindow = NULL;

    Controls* controls;
};