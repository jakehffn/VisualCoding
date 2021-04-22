#pragma once

#include <SDL.h>

class Clock {
public:
    Clock();
    double getDeltaTime();
    double tick();

private:
    Uint64 currentFrame;
    Uint64 lastFrame;

    double deltaTime;
};