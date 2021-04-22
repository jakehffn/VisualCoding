#pragma once

#include <SDL.h>

#include "consts.h"

class Input {
public:
    void update();
    int* getInputs();
    bool quitProgram();

private:
    int inputs[8]{0};
    SDL_Event e;
    bool quit;
};