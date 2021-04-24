#pragma once

#include <SDL.h>

#include "consts.h"

class Input {
public:
    Input();
    ~Input();
    void update();
    int* getInputs();
    bool quitProgram();

private:
    int* inputs;
    SDL_Event e;
    bool quit;
};